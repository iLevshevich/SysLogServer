#ifndef __TYPE_REPOSITORY_H_INCLUDED__ 
#define __TYPE_REPOSITORY_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace DataBase{

	class TypeRepository:
		public DataBase::BaseRepository{
	public:
		typedef DataBase::BaseRepository::sql_type sql_type;

		TypeRepository();
		virtual ~TypeRepository();

	protected:
		virtual boost::call_traits< sql_type >::value_type getSqlSelectRequest() const;
		virtual boost::call_traits< sql_type >::value_type getSqlInsertRequest() const;
	};

};

#pragma pack( pop )

#endif //__TYPE_REPOSITORY_H_INCLUDED__