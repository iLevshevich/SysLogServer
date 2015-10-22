#ifndef __OPTIONS_DECORATOR_H_INCLUDED__ 
#define __OPTIONS_DECORATOR_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace Utility{

	class OptionsDecorator: 
				private boost::noncopyable{
	public:
		typedef Utility::Options::value_type value_type;
		typedef Utility::Options::key_type key_type;

		OptionsDecorator();

		boost::call_traits< value_type >::value_type __fastcall get( boost::call_traits< key_type >::const_reference ) const;
	private:
		boost::scoped_ptr< Utility::Options > pimpl;
	};

};

#pragma pack( pop )

#endif //__OPTIONS_DECORATOR_H_INCLUDED__