#include "stdafx.h"
#include "IRepository.h"
#include "BaseRepository.h"
#include "TypeRepository.h"

DataBase::TypeRepository::TypeRepository():
	DataBase::BaseRepository(){}

DataBase::TypeRepository::~TypeRepository(){}

boost::call_traits< DataBase::TypeRepository::sql_type >::value_type DataBase::TypeRepository::getSqlSelectRequest() const{
	return boost::call_traits< DataBase::TypeRepository::sql_type >::value_type( _T("SELECT [Id] FROM [dbo].[EventLogType] WHERE [name] = ?;") );
}

boost::call_traits< DataBase::TypeRepository::sql_type >::value_type DataBase::TypeRepository::getSqlInsertRequest() const{
	return boost::call_traits< DataBase::TypeRepository::sql_type >::value_type( _T("INSERT INTO [dbo].[EventLogType] ([name]) VALUES (?);") );
}