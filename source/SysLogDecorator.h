#ifndef __SYS_LOG_DECORATOR_H_INCLUDED__ 
#define __SYS_LOG_DECORATOR_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace EntryPoint{

	class SysLogDecorator: 
				private boost::noncopyable{
	public:
		SysLogDecorator();

		void run();
		void stop();

		void __fastcall producer( Command::ICommand* const );
	private:
		boost::shared_ptr< EntryPoint::SysLog > pimpl;
	};

};

#pragma pack( pop )

#endif //__SYS_LOG_DECORATOR_H_INCLUDED__