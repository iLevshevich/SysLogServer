#include "stdafx.h"
#include "Buffer.h"
#include "Singleton.h"
#include "ICommand.h"
#include "Options.h"
#include "OptionsDecorator.h"
#include "SysLog.h"
#include "SysLogDecorator.h"
#include "lexical_cast_.h"
#include "Utility.h"
#include "UdpAsyncServer.h"
#include "UdpAsyncServerDecorator.h"

EntryPoint::UdpAsyncServerDecorator::UdpAsyncServerDecorator():
		pimpl( nullptr ),
		io_service_manager( nullptr ){
	Utility::OptionsDecorator& options( Memmory::Singleton< Utility::OptionsDecorator >::Instance() );
	{
		const short server_port( boost::lexical_cast< short >( options.get( "server_port" ) ) );
		pimpl = boost::shared_ptr< EntryPoint::UdpAsyncServer >( new EntryPoint::UdpAsyncServer( io_service, server_port ) );
	}
}

void EntryPoint::UdpAsyncServerDecorator::run(){
	EntryPoint::SysLogDecorator& syslog( Memmory::Singleton< EntryPoint::SysLogDecorator >::Instance() );
	{
		syslog.run();
	}

	io_service_manager = boost::shared_ptr< boost::thread >( new boost::thread( [this](){
		try{
			io_service.reset();
			io_service.run();
		}catch( const boost::thread_interrupted& ){
#if defined(__TRACERT__)
			const std::wstring warn_message( boost::lexical_cast< std::wstring >( ( boost::format( "EntryPoint::UdpAsyncServerDecorator::run()->Interrupted: %s" ) % boost::this_thread::get_id() ).str() ) );
			Utility::to_warn_event_log( warn_message );
#endif
		}catch( const std::runtime_error& er ){
			const std::wstring error_message( boost::lexical_cast< std::wstring >( ( boost::format( "EntryPoint::UdpAsyncServerDecorator::run()->%s" ) % er.what() ).str() ) );
			Utility::to_error_event_log( error_message );
		}catch(...){
			Utility::to_error_event_log( boost::lexical_cast< std::wstring >( _T("EntryPoint::UdpAsyncServerDecorator::run()->Unknown Error!" ) ) );
		}
	} ) );
}
		
void EntryPoint::UdpAsyncServerDecorator::stop(){
	io_service.stop();

	{
		io_service_manager->interrupt();
		io_service_manager->timed_join( boost::posix_time::seconds( timejoin ) );
	}

	EntryPoint::SysLogDecorator& syslog( Memmory::Singleton< EntryPoint::SysLogDecorator >::Instance() );
	{
		syslog.stop();
	}
}
		