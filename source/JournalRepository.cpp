#include "stdafx.h"
#include "IRepository.h"
#include "BaseRepository.h"
#include "JournalRepository.h"

DataBase::JournalRepository::JournalRepository():
		DataBase::BaseRepository(){}

DataBase::JournalRepository::~JournalRepository(){}

boost::call_traits< DataBase::JournalRepository::sql_type >::value_type DataBase::JournalRepository::getSqlSelectRequest() const{
	return boost::call_traits< DataBase::JournalRepository::sql_type >::value_type( _T("SELECT [Id] FROM [dbo].[EventLogJournal] WHERE [name] = ?;") );
}

boost::call_traits< DataBase::JournalRepository::sql_type >::value_type DataBase::JournalRepository::getSqlInsertRequest() const{
	return boost::call_traits< DataBase::JournalRepository::sql_type >::value_type( _T("INSERT INTO [dbo].[EventLogJournal] ([name]) VALUES (?);") );
}