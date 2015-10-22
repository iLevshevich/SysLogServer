#ifndef __UDP_ASYNC_SERVER_DECORATOR_H_INCLUDED__ 
#define __UDP_ASYNC_SERVER_DECORATOR_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace EntryPoint{

	class UdpAsyncServerDecorator: 
				private boost::noncopyable{
	public:
		UdpAsyncServerDecorator();

		void run();
		void stop();

	private:
		enum{ timejoin = 30 };

		boost::asio::io_service io_service;
		boost::shared_ptr< boost::thread > io_service_manager;
		boost::shared_ptr< EntryPoint::UdpAsyncServer > pimpl;
	};

};

#pragma pack( pop )

#endif //__UDP_ASYNC_SERVER_DECORATOR_H_INCLUDED__