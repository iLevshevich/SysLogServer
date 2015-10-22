#ifndef __UDP_ASYNC_SERVER_H_INCLUDED__ 
#define __UDP_ASYNC_SERVER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace EntryPoint{

	class UdpAsyncServer: 
				private boost::noncopyable{
	public:
		explicit UdpAsyncServer( boost::asio::io_service&, short );

	private:
		void receive();

		boost::asio::ip::udp::socket socket_;
		boost::asio::ip::udp::endpoint sender_endpoint_;

		enum { buffer_max_length = 64*1024 };
		Memmory::Buffer< char > buffer_;
	};

};

#pragma pack( pop )

#endif //__UDP_ASYNC_SERVER_H_INCLUDED__
