#include "stdafx.h"
#include "Options.h"

void Utility::Options::init( int argc, _TCHAR* argv[] ){
	boost::program_options::options_description desc("Service options");

	desc.add_options()
			( "workers_count", boost::program_options::value< boost::call_traits< Utility::Options::value_type >::value_type >()->default_value( 
									boost::lexical_cast< boost::call_traits< Utility::Options::value_type >::value_type >( getProcessorCount() << 1 ) ) )
			( "server_port", boost::program_options::value< boost::call_traits< Utility::Options::value_type >::value_type >()->default_value( "514" ) ) // default UDP port syslog
			( "connection_string", boost::program_options::value< boost::call_traits< Utility::Options::value_type >::value_type >()->default_value( "Provider=SQLOLEDB.1;Server=lpc:test-devsrv;Database=TestDB;Trusted_Connection=yes;Connect Timeout=1800;" ) );

    boost::program_options::store(boost::program_options::parse_command_line( argc, argv, desc ), vm);
}

boost::call_traits< Utility::Options::value_type >::value_type Utility::Options::get( boost::call_traits< Utility::Options::key_type >::const_reference key ) const{
	return vm[ key ].as< boost::call_traits< Utility::Options::value_type >::value_type >();
}

std::size_t Utility::Options::getProcessorCount() const{
	SYSTEM_INFO sysinfo;
	memset( &sysinfo, 0, sizeof( SYSTEM_INFO ) );
    ::GetSystemInfo( &sysinfo );
    return sysinfo.dwNumberOfProcessors;
}