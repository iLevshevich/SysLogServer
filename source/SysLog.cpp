#include "stdafx.h"
#include "Singleton.h"
#include "ICommand.h"
#include "ConsumerCommand.h"
#include "IRepository.h"
#include "BaseRepository.h"
#include "SourceRepository.h"
#include "TypeRepository.h"
#include "MessageRepository.h"
#include "MachineRepository.h"
#include "JournalRepository.h"
#include "LogDAO.h"
#include "SysLogDAO.h"
#include "COMState.h"
#include "COMSessionInitializer.h"
#include "lexical_cast_.h"
#include "Utility.h"
#include "SysLog.h"

EntryPoint::SysLog::SysLog( const std::size_t& thread_count_ ):
				queue( capacity_size ),
				thread_count( ( thread_count_ > thread_count_max )? thread_count_max: thread_count_ ){
	for( std::size_t counter( 0 ); counter < thread_count; ++ counter ){
		consumer_threads.create_thread( boost::bind( &EntryPoint::SysLog::consumer, this ) );			
	}
	mutex.lock();
}

EntryPoint::SysLog::~SysLog(){
	consumer_threads.interrupt_all();
	consumer_threads.join_all();
}

void EntryPoint::SysLog::producer( Command::ICommand* const command ){
	if( !queue.push( command ) ){
		throw std::runtime_error( ( boost::format( "EntryPoint::SysLog::producer()->%s" ) % "queue.push() failed" ).str() );
	}

	condition.notify_one();
}

void EntryPoint::SysLog::consumer(){
	try{
		COM::COMSessionInitializer com_session;
		if( com_session.isFailed() ){
			_com_issue_error( com_session.getResultCode() );
		}

		boost::xtime time;
		memset( &time, 0, sizeof( boost::xtime ) );

		boost::shared_ptr< Command::ConsumerCommand::dao_type > thread_dao( new Command::ConsumerCommand::dao_type() );

		while ( true ) {

			{
				boost::unique_lock< boost::mutex > lock( mutex );

				boost::this_thread::interruption_point(); 
				
				if( queue.empty() )
				{
					boost::xtime_get( &time, boost::TIME_UTC_ );
					time.nsec += timeout;

					condition.timed_wait( lock, time );
				}
			}
				
			if( !queue.empty() ){

				boost::this_thread::interruption_point();

				Command::ICommand* command( nullptr );
				if( queue.pop( command ) ){
					boost::this_thread::disable_interruption di;

					if( command ){
						boost::scoped_ptr< Command::ICommand > command_ptr( command );
						{
							Command::ConsumerCommand* const consumer_command( reinterpret_cast< Command::ConsumerCommand* >( command ) );
							consumer_command->setDAO( thread_dao );
						}
						command_ptr->execute();
					}
				}					
			}
		}

	}catch( const boost::thread_interrupted& ){
		//std::cerr << "Interrupted: " << boost::this_thread::get_id() << std::endl;
	}catch( const _com_error& ce ){
		const std::wstring error_message( 
				boost::lexical_cast< std::wstring >( 
				( boost::format( "EntryPoint::SysLog::consumer()->source: %s, message: %s, description: %s" ) % ce.Source() % ce.ErrorMessage() % ce.Description() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch( const std::runtime_error& er ){
		const std::wstring error_message( boost::lexical_cast< std::wstring >( ( boost::format( "EntryPoint::SysLog::consumer()->%s" ) % er.what() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch(...){
		Utility::to_error_event_log( boost::lexical_cast< std::wstring >( _T("EntryPoint::SysLog::consumer()->Unknown Error!" ) ) );
	}
}

void EntryPoint::SysLog::run(){
	mutex.unlock();
}
		
void EntryPoint::SysLog::stop(){
	mutex.lock();	
}