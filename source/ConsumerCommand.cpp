#include "stdafx.h"
#include "ICommand.h"
#include "SyslogParser.h"
#include "QnapParser.h"
#include "LogDAO.h"
#include "SysLogDAO.h"
#include "SysLogSeverityType.h"
#include "lexical_cast_.h"
#include "Utility.h"
#include "ConsumerCommand.h"

Command::ConsumerCommand::ConsumerCommand( boost::call_traits< Command::ConsumerCommand::param_type >::const_reference data_ ):
	data( data_ ),
	dao_ptr( nullptr ){}

Command::ConsumerCommand::~ConsumerCommand(){}

void Command::ConsumerCommand::execute(){
	try{
		if( !dao_ptr ){
			throw std::runtime_error( "Invalid DAO" );
		}
		
		Utility::SyslogParser< Utility::QnapParser > parser( data );
		{
			parser.parse();
		}

		if( !isSkip( parser.getSeverityType() ) ){
			dao_ptr->insert( parser );
		}

	}catch( const _com_error& ce ){
		const std::wstring error_message( 
				boost::lexical_cast< std::wstring >( 
				( boost::format( "Command::ConsumerCommand::execute()->source: %s, message: %s, description: %s" ) % ce.Source() % ce.ErrorMessage() % ce.Description() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch( const std::runtime_error& er ){
		const std::wstring error_message( boost::lexical_cast< std::wstring >( ( boost::format( "Command::ConsumerCommand::execute()->%s" ) % er.what() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch(...){
		Utility::to_error_event_log( boost::lexical_cast< std::wstring >( _T("Command::ConsumerCommand::execute()->Unknown Error!" ) ) );
	}
}

bool Command::ConsumerCommand::isSkip( boost::call_traits< Command::ConsumerCommand::param_type >::const_reference type ) const{
	return Utility::SysLogSeverityType::isUnKnown( type );
}

void Command::ConsumerCommand::setDAO( boost::call_traits< boost::shared_ptr< boost::call_traits< Command::ConsumerCommand::dao_type >::value_type > >::const_reference dao_ ){
	dao_ptr = dao_;
}




