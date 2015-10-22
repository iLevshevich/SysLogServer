#include "stdafx.h"
#include "SyslogFacility.h"
#include "SysLogSeverity.h"
#include "SysLogSeverityType.h"
#include "QnapParser.h"

Utility::SysLogSeverity Utility::QnapParser::severity_map;
Utility::SyslogFacility Utility::QnapParser::facility_map;
Utility::SysLogSeverityType Utility::QnapParser::severity_type_map;

Utility::QnapParser::QnapParser( boost::call_traits< Utility::QnapParser::param_type >::const_reference parse_data_ ):
		parse_data( parse_data_ ),
		MS_CTX( "event log:" ),
		CN_CTX( "Content:" ),
		SP( ' ' ),
		PRI_START( '<' ),
		PRI_END( '>' ),
		SD_START( '[' ),
		SD_END( ']' ){}

void Utility::QnapParser::parse(){
	//PRIVAL
	const param_type::size_type pri_start( parse_data.find_first_of( PRI_START ) );
	if( pri_start == param_type::npos ){
		throw std::runtime_error( ( boost::format( "Utility::QnapParser::parse() failed with: %s" ) % "simbol '<' is missing" ).str() );
	}

	const param_type::size_type pri_end( parse_data.find_first_of( PRI_END ) );
	if( pri_end == param_type::npos ){
		throw std::runtime_error( ( boost::format( "Utility::QnapParser::parse() failed with: %s" ) % "simbol '>' is missing" ).str() );
	}

	const std::size_t prival( boost::lexical_cast< std::size_t >( parse_data.substr( pri_start + 1, ( pri_end - pri_start ) - 1 ) ) );

	facility_level = prival >> 3;
	facility = facility_map.get( facility_level );

	severity_level = prival % 8;
	severity = severity_map.get( severity_level );

	severity_type = severity_type_map.get( severity_level );
	
	//ProcId
	const param_type::size_type sd_start( parse_data.find_first_of( SD_START ) );
	if( sd_start == param_type::npos ){
		throw std::runtime_error( ( boost::format( "Utility::QnapParser::parse() failed with: %s" ) % "simbol '[' is missing" ).str() );
	}

	const param_type::size_type sd_end( parse_data.find_first_of( SD_END ) );
	if( sd_end == param_type::npos ){
		throw std::runtime_error( ( boost::format( "Utility::QnapParser::parse() failed with: %s" ) % "simbol ']' is missing" ).str() );
	}

	proc_id =  parse_data.substr( sd_start + 1, ( sd_end - sd_start ) - 1 );

	//datatime + hostname + appname
	const param_type dha( parse_data.substr( pri_end + 1, ( sd_start - pri_end ) - 1 ) );
    
	//AppName
	const param_type::size_type app_sp_start( dha.find_last_of( SP ) );
	if( app_sp_start == param_type::npos ){
		throw std::runtime_error( ( boost::format( "Utility::QnapParser::parse() failed with: %s" ) % "simbol ' ' is missing" ).str() );
	}

	const param_type::size_type app_sp_end( dha.length() );

	app_name = dha.substr( app_sp_start + 1, ( app_sp_end - app_sp_start ) - 1 );

	//datatime + hostname
	const param_type dh( dha.substr( 0, app_sp_start ) );

	//HostName
	const param_type::size_type host_sp_start( dh.find_last_of( SP ) );
	if( host_sp_start == param_type::npos ){
		throw std::runtime_error( ( boost::format( "Utility::QnapParser::parse() failed with: %s" ) % "simbol ' ' is missing" ).str() );
	}

	const param_type::size_type host_sp_end( dh.length() );

	host_name = dh.substr( host_sp_start + 1, ( host_sp_end - host_sp_start ) - 1 );

	//TimeStamp
	const param_type::size_type time_sp_start( 0 );

	const param_type::size_type time_sp_end( dh.find_last_of( SP ) );
	if( time_sp_end == param_type::npos ){
		throw std::runtime_error( ( boost::format( "Utility::QnapParser::parse() failed with: %s" ) % "simbol ' ' is missing" ).str() );
	}

	time_stamp = dh.substr( time_sp_start, time_sp_end);

	//Message
	param_type::size_type message_sp_start( parse_data.find( MS_CTX ) );
	if( message_sp_start == param_type::npos ){
		throw std::runtime_error( ( boost::format( "Utility::QnapParser::parse() failed with: %s" ) % "string 'event log:' is missing" ).str() );
	}else{
		message_sp_start += MS_CTX.length();
	}
	const param_type::size_type message_sp_end( parse_data.length() );

	message = parse_data.substr( message_sp_start + 1, message_sp_end - message_sp_start );

	//Content
	boost::char_separator< param_type::value_type > simbol(",");
	boost::tokenizer< boost::char_separator< param_type::value_type > > tokens( message, simbol );
	for( boost::tokenizer< boost::char_separator< param_type::value_type > >::const_iterator iter( tokens.begin() ); iter != tokens.end(); ++iter ){
		param_type::size_type content_start( iter->find( CN_CTX ) );
		if( content_start != param_type::npos ){
			content_start += CN_CTX.length();
			const param_type::size_type content_end( iter->length() );
			content = iter->substr( content_start + 1, content_end - content_start );

			break;
		}
	}
}