#ifndef __OPTIONS_H_INCLUDED__ 
#define __OPTIONS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace Utility{

	class Options: 
				private boost::noncopyable{
	public:
		typedef std::string value_type;
		typedef std::string key_type;

		void __fastcall init( int argc, _TCHAR* argv[] );
		boost::call_traits< value_type >::value_type __fastcall get( boost::call_traits< key_type >::const_reference ) const;

	private:
		std::size_t getProcessorCount() const;

		boost::program_options::variables_map vm;
	};

};

#pragma pack( pop )

#endif //__OPTIONS_H_INCLUDED__

