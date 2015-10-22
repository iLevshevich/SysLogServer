#include "stdafx.h"
#include "lexical_cast_.h"
#include "Singleton.h"
#include "Options.h"
#include "OptionsDecorator.h"
#include "IRepository.h"
#include "BaseRepository.h"
#include "SourceRepository.h"
#include "TypeRepository.h"
#include "MessageRepository.h"
#include "MachineRepository.h"
#include "JournalRepository.h"
#include "SyslogParser.h"
#include "QnapParser.h"
#include "Utility.h"
#include "LogDAO.h"

DataBase::LogDAO::LogDAO():
	machine_repository( new DataBase::LogDAO::machine_repository_type() ),
	message_repository( new DataBase::LogDAO::message_repository_type() ),
	source_repository( new DataBase::LogDAO::source_repository_type() ),
	type_repository( new DataBase::LogDAO::type_repository_type() ),
	journal_repository( new DataBase::LogDAO::journal_repository_type() ){
		Utility::OptionsDecorator& options( Memmory::Singleton< Utility::OptionsDecorator >::Instance() );
		{
			connection_string = options.get( "connection_string" ).c_str();
		}
}

boost::call_traits< DataBase::LogDAO::sql_type >::value_type DataBase::LogDAO::getSqlInsertRequest() const{
	return "INSERT INTO [dbo].[EventLog] ([event_log_type_id],[event_log_source_id],[event_log_machine_id],[event_log_journal_id],[event_log_message_id],[time_generated],[time_written],[record_number],[event_id],[event_category]) VALUES (?,?,?,?,?,?,?,?,?,?);";}

void DataBase::LogDAO::insert( boost::call_traits< DataBase::LogDAO::parser_type >::const_reference parser ){
	try{
		ADODB::_ConnectionPtr connection( nullptr );
		{
			const HRESULT connection_result( connection.CreateInstance( __uuidof( ADODB::Connection ) ) );
			if( FAILED(connection_result) ){
				::_com_issue_error( connection_result );
			}

			connection->Mode = ADODB::ConnectModeEnum::adModeWrite;

			const HRESULT open_result( connection->Open( connection_string, _T(""), _T(""), ADODB::adConnectUnspecified ) );
			if( FAILED(open_result) ){
				::_com_issue_error( open_result );
			}
		}
		
		ADODB::_CommandPtr command( nullptr );
		{
			const HRESULT command_result( command.CreateInstance( __uuidof( ADODB::Command ) ) );
			if( FAILED(command_result) ){
				::_com_issue_error( command_result );
			}

			command->ActiveConnection = connection;
			command->CommandText = getSqlInsertRequest();
			command->PutPrepared( true );
		}
	
		ADODB::_ParameterPtr parameter( nullptr );
		{
			const HRESULT parameter_result( parameter.CreateInstance( __uuidof( ADODB::Parameter ) ) );
			if( FAILED(parameter_result) ){
				::_com_issue_error( parameter_result );
			}

			{//event_log_type_id
				const DataBase::LogDAO::type_repository_type::return_type type_id( type_repository->get( parser.getSeverityType() ) );
				const _bstr_t key_value( boost::lexical_cast< _bstr_t >( type_id ) );
				const std::size_t key_length( key_value.length() );

				VARIANT parameter_value;
				{
					parameter_value.vt = VT_BSTR;
					parameter_value.bstrVal = key_value;
				}

				parameter = command->CreateParameter(	_T(""), 
														ADODB::DataTypeEnum::adGUID, 
														ADODB::ParameterDirectionEnum::adParamInput,  
														key_length, 
														parameter_value );

				const HRESULT append_result( command->Parameters->Append( parameter ) );
				if( FAILED(append_result) ){
					::_com_issue_error( append_result );
				}
			}

			{//event_log_source_id
				const DataBase::LogDAO::source_repository_type::return_type source_id( source_repository->get( parser.getAppName() ) );
				const _bstr_t key_value( boost::lexical_cast< _bstr_t >( source_id ) );
				const std::size_t key_length( key_value.length() );

				VARIANT parameter_value;
				{
					parameter_value.vt = VT_BSTR;
					parameter_value.bstrVal = key_value;
				}

				parameter = command->CreateParameter(	_T(""), 
														ADODB::DataTypeEnum::adGUID, 
														ADODB::ParameterDirectionEnum::adParamInput,  
														key_length, 
														parameter_value );

				const HRESULT append_result( command->Parameters->Append( parameter ) );
				if( FAILED(append_result) ){
					::_com_issue_error( append_result );
				}
			}

			{//event_log_machine_id
				const DataBase::LogDAO::machine_repository_type::return_type machine_id( machine_repository->get( parser.getHostName() ) );
				const _bstr_t key_value( boost::lexical_cast< _bstr_t >( machine_id ) );
				const std::size_t key_length( key_value.length() );

				VARIANT parameter_value;
				{
					parameter_value.vt = VT_BSTR;
					parameter_value.bstrVal = key_value;
				}

				parameter = command->CreateParameter(	_T(""), 
														ADODB::DataTypeEnum::adGUID, 
														ADODB::ParameterDirectionEnum::adParamInput,  
														key_length, 
														parameter_value );

				const HRESULT append_result( command->Parameters->Append( parameter ) );
				if( FAILED(append_result) ){
					::_com_issue_error( append_result );
				}
			}

			{//event_log_journal_id
				const DataBase::LogDAO::journal_repository_type::return_type journal_id( journal_repository->get( "Application" ) );
				const _bstr_t key_value( boost::lexical_cast< _bstr_t >( journal_id ) );
				const std::size_t key_length( key_value.length() );

				VARIANT parameter_value;
				{
					parameter_value.vt = VT_BSTR;
					parameter_value.bstrVal = key_value;
				}

				parameter = command->CreateParameter(	_T(""), 
														ADODB::DataTypeEnum::adGUID, 
														ADODB::ParameterDirectionEnum::adParamInput,  
														key_length, 
														parameter_value );

				const HRESULT append_result( command->Parameters->Append( parameter ) );
				if( FAILED(append_result) ){
					::_com_issue_error( append_result );
				}
			}

			{//event_log_message_id
				const DataBase::LogDAO::message_repository_type::return_type message_id( message_repository->get( parser.getMessage() ) );
				const _bstr_t key_value( boost::lexical_cast< _bstr_t >( message_id ) );
				const std::size_t key_length( key_value.length() );

				VARIANT parameter_value;
				{
					parameter_value.vt = VT_BSTR;
					parameter_value.bstrVal = key_value;
				}

				parameter = command->CreateParameter(	_T(""), 
														ADODB::DataTypeEnum::adGUID, 
														ADODB::ParameterDirectionEnum::adParamInput,  
														key_length, 
														parameter_value );

				const HRESULT append_result( command->Parameters->Append( parameter ) );
				if( FAILED(append_result) ){
					::_com_issue_error( append_result );
				}
			}

			{//time_generated
				VARIANT parameter_value;
				{
					parameter_value.vt = VT_DATE;
					parameter_value.date = ATL::COleDateTime::GetCurrentTime();
				}

				parameter = command->CreateParameter(	_T(""), 
														ADODB::DataTypeEnum::adDate, 
														ADODB::ParameterDirectionEnum::adParamInput,  
														-1, 
														parameter_value );

				const HRESULT append_result( command->Parameters->Append( parameter ) );
				if( FAILED(append_result) ){
					::_com_issue_error( append_result );
				}
			}

			{//time_written
				VARIANT parameter_value;
				{
					parameter_value.vt = VT_DATE;
					parameter_value.date = ATL::COleDateTime::GetCurrentTime();
				}

				parameter = command->CreateParameter(	_T(""), 
														ADODB::DataTypeEnum::adDate, 
														ADODB::ParameterDirectionEnum::adParamInput,  
														-1, 
														parameter_value );

				const HRESULT append_result( command->Parameters->Append( parameter ) );
				if( FAILED(append_result) ){
					::_com_issue_error( append_result );
				}
			}

			{//record_number
				const _bstr_t key_value( _T("0") );
				const std::size_t key_length( key_value.length() );

				VARIANT parameter_value;
				{
					parameter_value.vt = VT_BSTR;
					parameter_value.bstrVal = key_value;
				}

				parameter = command->CreateParameter(	_T(""), 
														ADODB::DataTypeEnum::adVarWChar, 
														ADODB::ParameterDirectionEnum::adParamInput,  
														key_length, 
														parameter_value );

				const HRESULT append_result( command->Parameters->Append( parameter ) );
				if( FAILED(append_result) ){
					::_com_issue_error( append_result );
				}
			}

			{//event_id
				const _bstr_t key_value(_T("0") );
				const std::size_t key_length( key_value.length() );

				VARIANT parameter_value;
				{
					parameter_value.vt = VT_BSTR;
					parameter_value.bstrVal = key_value;
				}

				parameter = command->CreateParameter(	_T(""), 
														ADODB::DataTypeEnum::adVarWChar, 
														ADODB::ParameterDirectionEnum::adParamInput,  
														key_length, 
														parameter_value );

				const HRESULT append_result( command->Parameters->Append( parameter ) );
				if( FAILED(append_result) ){
					::_com_issue_error( append_result );
				}
			}

			{//event_category
				const _bstr_t key_value( _T("0") );
				const std::size_t key_length( key_value.length() );

				VARIANT parameter_value;
				{
					parameter_value.vt = VT_BSTR;
					parameter_value.bstrVal = key_value;
				}

				parameter = command->CreateParameter(	_T(""), 
														ADODB::DataTypeEnum::adVarWChar, 
														ADODB::ParameterDirectionEnum::adParamInput,  
														key_length, 
														parameter_value );

				const HRESULT append_result( command->Parameters->Append( parameter ) );
				if( FAILED(append_result) ){
					::_com_issue_error( append_result );
				}
			}

		}

		try{
			const long transaction_id( connection->BeginTrans() );
			{
				command->Execute( nullptr, nullptr, ADODB::CommandTypeEnum::adCmdText );
			}
			const HRESULT commit_result( connection->CommitTrans() );
			if( FAILED(commit_result) ){
				::_com_issue_error( commit_result );
			}
		
		}catch( const _com_error& ce ){
			const std::wstring error_message( 
				boost::lexical_cast< std::wstring >( 
				( boost::format( "DataBase::LogDAO::insert()::CommitTrans()->source: %s, message: %s, description: %s" ) % ce.Source() % ce.ErrorMessage() % ce.Description() ).str() ) );
			Utility::to_error_event_log( error_message );

			const HRESULT rollback_result( connection->RollbackTrans() );
			if( FAILED(rollback_result) ){
				::_com_issue_error( rollback_result );
			}
		}

		if( connection && connection->State == ADODB::adStateOpen ){
			const HRESULT close_result( connection->Close() );
			if( FAILED(close_result) ){
				::_com_issue_error( close_result );
			}
		}

	}catch( const _com_error& ce ){
		const std::wstring error_message( 
				boost::lexical_cast< std::wstring >( 
				( boost::format( "DataBase::LogDAO::insert()->source: %s, message: %s, description: %s" ) % ce.Source() % ce.ErrorMessage() % ce.Description() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch( const std::runtime_error& er ){
		const std::wstring error_message( boost::lexical_cast< std::wstring >( ( boost::format( "DataBase::LogDAO::insert()->%s" ) % er.what() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch(...){
		Utility::to_error_event_log( boost::lexical_cast< std::wstring >( _T("DataBase::LogDAO::insert()->Unknown Error!" ) ) );
	}
}
