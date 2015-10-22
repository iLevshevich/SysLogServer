#ifndef __LOG_DAO_H_INCLUDED__ 
#define __LOG_DAO_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace DataBase{

	class LogDAO: 
		private boost::noncopyable{
	public:
		typedef boost::call_traits< Utility::SyslogParser< Utility::QnapParser > >::value_type parser_type;
		typedef boost::call_traits< DataBase::MachineRepository >::value_type machine_repository_type;
		typedef boost::call_traits< DataBase::MessageRepository >::value_type message_repository_type;
		typedef boost::call_traits< DataBase::SourceRepository >::value_type source_repository_type;
		typedef boost::call_traits< DataBase::TypeRepository >::value_type type_repository_type;
		typedef boost::call_traits< DataBase::TypeRepository >::value_type type_repository_type;
		typedef boost::call_traits< DataBase::JournalRepository >::value_type journal_repository_type;
		typedef _bstr_t sql_type;

		LogDAO();

		void _fastcall insert( boost::call_traits< parser_type >::const_reference );

	private:
		boost::call_traits< sql_type >::value_type getSqlInsertRequest() const;

		boost::scoped_ptr< machine_repository_type > machine_repository;
		boost::scoped_ptr< message_repository_type > message_repository;
		boost::scoped_ptr< source_repository_type > source_repository;
		boost::scoped_ptr< type_repository_type > type_repository;
		boost::scoped_ptr< journal_repository_type > journal_repository;

		boost::call_traits< sql_type >::value_type connection_string;
	};

};

#pragma pack( pop )

#endif //__LOG_DAO_H_INCLUDED__
