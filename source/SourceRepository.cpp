#include "stdafx.h"
#include "IRepository.h"
#include "BaseRepository.h"
#include "SourceRepository.h"

DataBase::SourceRepository::SourceRepository():
		DataBase::BaseRepository(){}

DataBase::SourceRepository::~SourceRepository(){}

boost::call_traits< DataBase::SourceRepository::sql_type >::value_type DataBase::SourceRepository::getSqlSelectRequest() const{
	return boost::call_traits< DataBase::SourceRepository::sql_type >::value_type( _T("SELECT [Id] FROM [dbo].[EventLogSource] WHERE [name] = ?;") );
}

boost::call_traits< DataBase::SourceRepository::sql_type >::value_type DataBase::SourceRepository::getSqlInsertRequest() const{
	return boost::call_traits< DataBase::SourceRepository::sql_type >::value_type( _T("INSERT INTO [dbo].[EventLogSource] ([name]) VALUES (?);") );
}