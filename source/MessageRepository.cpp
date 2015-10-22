#include "stdafx.h"
#include "IRepository.h"
#include "lexical_cast_.h"
#include "BaseRepository.h"
#include "Utility.h"
#include "MessageRepository.h"

DataBase::MessageRepository::MessageRepository():
	DataBase::BaseRepository(){}

DataBase::MessageRepository::~MessageRepository(){}

boost::call_traits< DataBase::MessageRepository::sql_type >::value_type DataBase::MessageRepository::getSqlSelectRequest() const{
	return boost::call_traits< DataBase::MessageRepository::sql_type >::value_type( _T("[dbo].[getMessageId]") );
}

boost::call_traits< DataBase::MessageRepository::sql_type >::value_type DataBase::MessageRepository::getSqlInsertRequest() const{
	return boost::call_traits< DataBase::MessageRepository::sql_type >::value_type( _T("INSERT INTO [dbo].[EventLogMessage] ([message]) VALUES (?);") );
}

boost::call_traits< DataBase::MessageRepository::return_type >::value_type DataBase::MessageRepository::getSQLSelect( boost::call_traits< DataBase::MessageRepository::param_type >::const_reference key ){
	_bstr_t result( _T("") );
	try{
		ADODB::_ConnectionPtr connection( nullptr );
		{
			const HRESULT connection_result( connection.CreateInstance( __uuidof( ADODB::Connection ) ) );
			if( FAILED(connection_result) ){
				::_com_issue_error( connection_result );
			}

			connection->Mode = ADODB::ConnectModeEnum::adModeRead;

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
			command->CommandText = getSqlSelectRequest();
			command->PutPrepared( true );
			command->NamedParameters = VARIANT_TRUE;
		}
	
		ADODB::_ParameterPtr parameter( nullptr );
		{
			const HRESULT parameter_result( parameter.CreateInstance( __uuidof( ADODB::Parameter ) ) );
			if( FAILED(parameter_result) ){
				::_com_issue_error( parameter_result );
			}

			{
				VARIANT parameter_value;
				{
					parameter_value.vt = VT_BSTR;
					parameter_value.bstrVal = nullptr;
				}

				parameter = command->CreateParameter(	_T("@RC"), 
														ADODB::DataTypeEnum::adVarWChar, 
														ADODB::ParameterDirectionEnum::adParamOutput,  
														36, 
														parameter_value );

				const HRESULT append_result( command->Parameters->Append( parameter ) );
				if( FAILED(append_result) ){
					::_com_issue_error( append_result );
				}
			}

			{
				VARIANT parameter_value;
				{
					parameter_value.vt = VT_BSTR;
					parameter_value.bstrVal = boost::lexical_cast< _bstr_t >( key );
				}

				parameter = command->CreateParameter(	_T("@message"), 
														ADODB::DataTypeEnum::adLongVarWChar, 
														ADODB::ParameterDirectionEnum::adParamInput,  
														-1, 
														parameter_value );

				const HRESULT append_result( command->Parameters->Append( parameter ) );
				if( FAILED(append_result) ){
					::_com_issue_error( append_result );
				}
			}
		}

		command->Execute( nullptr, nullptr, ADODB::CommandTypeEnum::adCmdStoredProc | ADODB::adExecuteNoRecords );

		VARIANT return_value = command->Parameters->Item[ _T("@RC" )]->GetValue();
		if( return_value.bstrVal != nullptr ){
			result = _T("{") + _bstr_t( return_value.bstrVal ) + _T("}");
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
				( boost::format( "DataBase::MessageRepository::getSQLSelect()->source: %s, message: %s, description: %s" ) % ce.Source() % ce.ErrorMessage() % ce.Description() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch( const std::runtime_error& er ){
		const std::wstring error_message( boost::lexical_cast< std::wstring >( ( boost::format( "DataBase::MessageRepository::getSQLSelect()->%s" ) % er.what() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch(...){
		Utility::to_error_event_log( boost::lexical_cast< std::wstring >( _T("DataBase::MessageRepository::getSQLSelect()->Unknown Error!" ) ) );
	}

	return boost::call_traits< DataBase::MessageRepository::return_type >::value_type( result );
}