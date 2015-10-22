#include "stdafx.h"
#include "IRepository.h"
#include "BaseRepository.h"
#include "MachineRepository.h"

DataBase::MachineRepository::MachineRepository():
		DataBase::BaseRepository(){}

DataBase::MachineRepository::~MachineRepository(){}

boost::call_traits< DataBase::MachineRepository::sql_type >::value_type DataBase::MachineRepository::getSqlSelectRequest() const{
	return boost::call_traits< DataBase::MachineRepository::sql_type >::value_type( _T("SELECT [Id] FROM [dbo].[EventLogMachine] WHERE [name] = ?;") );
}

boost::call_traits< DataBase::MachineRepository::sql_type >::value_type DataBase::MachineRepository::getSqlInsertRequest() const{
	return boost::call_traits< DataBase::MachineRepository::sql_type >::value_type( _T("INSERT INTO [dbo].[EventLogMachine] ([name]) VALUES (?);") );
}