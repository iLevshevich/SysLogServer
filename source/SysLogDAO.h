#ifndef __SYS_LOG_DAO_H_INCLUDED__ 
#define __SYS_LOG_DAO_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace DataBase{

	template< class T >
	class SysLogDAO: 
		private boost::noncopyable{
	public:
		typedef typename boost::call_traits< T >::value_type dao_type;
		typedef typename boost::call_traits< typename T::parser_type >::value_type parser_type;

		SysLogDAO():
			dao( new T() ){}

		void _fastcall insert( typename boost::call_traits< parser_type >::const_reference parser ){
			dao->insert( parser ); 
		}

	private:
		boost::scoped_ptr< dao_type > dao;
	};

};

#pragma pack( pop )

#endif //__SYS_LOG_DAO_H_INCLUDED__