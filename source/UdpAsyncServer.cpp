#include "stdafx.h"
#include "Buffer.h"
#include "Singleton.h"
#include "SysLog.h"
#include "SysLogDecorator.h"
#include "ICommand.h"
#include "ConsumerCommand.h"
#include "lexical_cast_.h"
#include "Utility.h"
#include "UdpAsyncServer.h"

EntryPoint::UdpAsyncServer::UdpAsyncServer( boost::asio::io_service& io_service, short port ): 
	socket_( io_service, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), port ) ),
	buffer_( buffer_max_length ){
		{
			const boost::asio::socket_base::receive_buffer_size option( buffer_max_length );
			socket_.set_option( option );
		}

		receive();
}

void EntryPoint::UdpAsyncServer::receive(){
	socket_.async_receive_from(
		boost::asio::buffer( buffer_.get(), buffer_max_length ), 
		sender_endpoint_,
		[this]( boost::system::error_code err, std::size_t bytes_recvd ){
			EntryPoint::SysLogDecorator& syslog( Memmory::Singleton< EntryPoint::SysLogDecorator >::Instance() ); 
			do{

				try{
#pragma warning( push )
//warning C4800: 'boost::system::error_code::unspecified_bool_type' : forcing value to bool 'true' or 'false' (performance warning)
#pragma warning ( disable:4800 )
					if( err ){
#pragma warning ( pop )
						const std::wstring error_message( boost::lexical_cast< std::wstring >( ( boost::format( "EntryPoint::UdpAsyncServer::receive()->%s" ) % boost::system::system_error( err ).what() ).str() ) );
						Utility::to_error_event_log( error_message );
					}else if( bytes_recvd > 0 ){
						syslog.producer( new Command::ConsumerCommand( boost::call_traits< Command::ConsumerCommand::param_type >::value_type( buffer_.get(), bytes_recvd ) ) );
					}

					bytes_recvd = socket_.receive_from( boost::asio::buffer( buffer_.get(), buffer_max_length ), sender_endpoint_, 0, err );

				}catch( const std::runtime_error& re ){
					const std::wstring error_message( boost::lexical_cast< std::wstring >( ( boost::format( "EntryPoint::UdpAsyncServer::receive()->%s" ) % re.what() ).str() ) );
					Utility::to_error_event_log( error_message );
				}catch(...){
					Utility::to_error_event_log( boost::lexical_cast< std::wstring >( _T("EntryPoint::UdpAsyncServer::receive()->Unknown Error!" ) ) );
				}

			}while( true );
		}
	);
}