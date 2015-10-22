#ifndef __I_REPOSITORY_H_INCLUDED__ 
#define __I_REPOSITORY_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace DataBase{
	
	class IRepository{
	public:
		typedef std::string param_type;
		typedef std::string return_type;

		virtual boost::call_traits< return_type >::value_type __fastcall get( boost::call_traits< param_type >::const_reference ) = 0;

		virtual ~IRepository(){}
	};

};

#pragma pack( pop )

#endif //__I_REPOSITORY_H_INCLUDED__