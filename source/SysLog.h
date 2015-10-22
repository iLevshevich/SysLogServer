#ifndef __SYS_LOG_H_INCLUDED__ 
#define __SYS_LOG_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace EntryPoint{

	class SysLog: 
		private boost::noncopyable{
	public:
		explicit SysLog( const std::size_t& );

		void run();
		void stop();

		~SysLog() throw();

		void __fastcall producer( Command::ICommand* const );
	private:
		void consumer();

		enum { thread_count_max = 64 };
		std::size_t thread_count;
		boost::thread_group consumer_threads;

		/*
		T must have a copy constructor
		T must have a trivial assignment operator
		T must have a trivial destructor
		*/
		enum { capacity_size = 4096 };
		boost::lockfree::queue< Command::ICommand* > queue;
		enum { timeout = 1000 * 1000 * 100 }; //nsec
		boost::condition_variable condition;
		boost::mutex mutex;
	};

};

#pragma pack( pop )

#endif //__SYS_LOG_H_INCLUDED__