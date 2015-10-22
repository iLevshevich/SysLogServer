#ifndef __MESSAGE_REPOSITORY_H_INCLUDED__ 
#define __MESSAGE_REPOSITORY_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace DataBase{

	class MessageRepository:
		public DataBase::BaseRepository{
	public:
		typedef DataBase::BaseRepository::param_type param_type;
		typedef DataBase::BaseRepository::return_type return_type;
		typedef DataBase::BaseRepository::sql_type sql_type;

		MessageRepository();
		virtual ~MessageRepository();

	protected:
		virtual boost::call_traits< sql_type >::value_type getSqlSelectRequest() const;
		virtual boost::call_traits< sql_type >::value_type getSqlInsertRequest() const;

	private:
		virtual boost::call_traits< return_type >::value_type __fastcall getSQLSelect( boost::call_traits< param_type >::const_reference ) override;
	};

};

#pragma pack( pop )

#endif //__MESSAGE_REPOSITORY_H_INCLUDED__

