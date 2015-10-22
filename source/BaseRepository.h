#ifndef __BASE_REPOSITORY_H_INCLUDED__ 
#define __BASE_REPOSITORY_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace DataBase{

	class BaseRepository:
		public DataBase::IRepository,
		private boost::noncopyable{
	public:
		typedef DataBase::IRepository::param_type param_type;
		typedef DataBase::IRepository::return_type return_type;
		typedef _bstr_t sql_type;

		BaseRepository();
		virtual ~BaseRepository();
		virtual boost::call_traits< return_type >::value_type __fastcall get( boost::call_traits< param_type >::const_reference );

	protected:
		virtual boost::call_traits< sql_type >::value_type getSqlSelectRequest() const = 0;
		virtual boost::call_traits< sql_type >::value_type getSqlInsertRequest() const = 0;

		boost::call_traits< sql_type >::value_type connection_string;

	private:
		virtual boost::call_traits< return_type >::value_type __fastcall getSQLSelect( boost::call_traits< param_type >::const_reference );
		virtual void __fastcall	getSQLInsert( boost::call_traits< param_type >::const_reference );

		typedef std::map< boost::call_traits< param_type >::value_type, boost::call_traits< return_type >::value_type > repository_type;
		repository_type repository;
	};

};

#pragma pack( pop )

#endif //__BASE_REPOSITORY_H_INCLUDED__