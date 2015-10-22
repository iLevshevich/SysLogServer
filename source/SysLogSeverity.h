#ifndef __SYS_LOG_SEVERITY_H_INCLUDED__ 
#define __SYS_LOG_SEVERITY_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace Utility{

	class SysLogSeverity: 
				private boost::noncopyable{
	public:
		typedef std::size_t key_type;
		typedef std::string value_type;

		SysLogSeverity();

		boost::call_traits< value_type >::const_reference __fastcall get( boost::call_traits< key_type >::const_reference ) const;
	private:
		void __fastcall add( boost::call_traits< key_type >::const_reference,
							 boost::call_traits< value_type >::const_reference );

		std::map< key_type, value_type > map_;
	};

};

#pragma pack( pop )

#endif //__SYS_LOG_SEVERITY_H_INCLUDED__

