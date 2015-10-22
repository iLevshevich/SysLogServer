#include "stdafx.h"
#include "IRepository.h"
#include "Singleton.h"
#include "Options.h"
#include "OptionsDecorator.h"
#include "lexical_cast_.h"
#include "Utility.h"
#include "BaseRepository.h"

DataBase::BaseRepository::BaseRepository(){
	Utility::OptionsDecorator& options( Memmory::Singleton< Utility::OptionsDecorator >::Instance() );
	{
		connection_string = options.get( "connection_string" ).c_str();
	}
}

DataBase::BaseRepository::~BaseRepository(){}

boost::call_traits< DataBase::BaseRepository::return_type >::value_type DataBase::BaseRepository::get( boost::call_traits< DataBase::BaseRepository::param_type >::const_reference key ){
	{
		const repository_type::const_iterator iter( repository.find( key ) );	
		if( iter != repository.end() ){
			return iter->second;
		}
	}

	{
		const boost::call_traits< DataBase::BaseRepository::return_type >::value_type value( getSQLSelect( key ) );
		if( !value.empty() ){
			repository.insert( std::make_pair( key, value ) );
		}else{
			getSQLInsert( key );
			const boost::call_traits< DataBase::BaseRepository::return_type >::value_type value_( getSQLSelect( key ) );
			if( value_.empty() ){
				throw std::runtime_error("Invalid database operation");
			}
			repository.insert( std::make_pair( key, value_ ) );
		}
	}

	{
		const repository_type::const_iterator iter( repository.find( key ) );	
		if( iter != repository.end() ){
			return iter->second;
		}else{
			throw std::runtime_error("Invalid repository operation");
		}
	}
}

boost::call_traits< DataBase::BaseRepository::return_type >::value_type DataBase::BaseRepository::getSQLSelect( boost::call_traits< DataBase::BaseRepository::param_type >::const_reference key ){
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
		}
	
		ADODB::_ParameterPtr parameter( nullptr );
		{
			const HRESULT parameter_result( parameter.CreateInstance( __uuidof( ADODB::Parameter ) ) );
			if( FAILED(parameter_result) ){
				::_com_issue_error( parameter_result );
			}

			const _bstr_t key_value( boost::lexical_cast< _bstr_t >( key ) );
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

		ADODB::_RecordsetPtr recordset( nullptr );
		{
			const HRESULT recordset_result( recordset.CreateInstance( __uuidof( ADODB::Recordset ) ) );
			if( FAILED(recordset_result) ){
				::_com_issue_error( recordset_result );
			}

			recordset = command->Execute( nullptr, nullptr, ADODB::CommandTypeEnum::adCmdText );

			while( !(recordset->ADOEOF) ){
				result = recordset->Fields->Item[ _T("Id") ]->Value;

				recordset->MoveNext(); 
			}
		}

		if( recordset && recordset->State == ADODB::adStateOpen ){
			const HRESULT close_result( recordset->Close() );
			if( FAILED(close_result) ){
				::_com_issue_error( close_result );
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
				( boost::format( "DataBase::BaseRepository::getSQLSelect()->source: %s, message: %s, description: %s" ) % ce.Source() % ce.ErrorMessage() % ce.Description() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch( const std::runtime_error& er ){
		const std::wstring error_message( boost::lexical_cast< std::wstring >( ( boost::format( "DataBase::BaseRepository::getSQLSelect()->%s" ) % er.what() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch(...){
		Utility::to_error_event_log( boost::lexical_cast< std::wstring >( _T("DataBase::BaseRepository::getSQLSelect()->Unknown Error!" ) ) );
	}

	return boost::call_traits< DataBase::BaseRepository::return_type >::value_type( result );
}

void DataBase::BaseRepository::getSQLInsert( boost::call_traits< DataBase::BaseRepository::param_type >::const_reference key ){
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

			const _bstr_t key_value( boost::lexical_cast< _bstr_t >( key ) );
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
				( boost::format( "DataBase::BaseRepository::getSQLInsert()::CommitTrans()->source: %s, message: %s, description: %s" ) % ce.Source() % ce.ErrorMessage() % ce.Description() ).str() ) );
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
				( boost::format( "DataBase::BaseRepository::getSQLInsert()->source: %s, message: %s, description: %s" ) % ce.Source() % ce.ErrorMessage() % ce.Description() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch( const std::runtime_error& er ){
		const std::wstring error_message( boost::lexical_cast< std::wstring >( ( boost::format( "DataBase::BaseRepository::getSQLInsert()->%s" ) % er.what() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch(...){
		Utility::to_error_event_log( boost::lexical_cast< std::wstring >( _T("DataBase::BaseRepository::getSQLInsert()->Unknown Error!" ) ) );
	}
}