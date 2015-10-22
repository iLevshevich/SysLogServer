#include "stdafx.h"
#include "SysLogSeverityType.h"

Utility::SysLogSeverityType::value_type Utility::SysLogSeverityType::Error( "Error" );
Utility::SysLogSeverityType::value_type Utility::SysLogSeverityType::Warning( "Warning" );
Utility::SysLogSeverityType::value_type Utility::SysLogSeverityType::UnKnown( "UnKnown" );

Utility::SysLogSeverityType::SysLogSeverityType(){
	add( 0, Error );
	add( 1, Error );
	add( 2, Error );
	add( 3, Error );
	add( 4, Warning );
	add( 5, UnKnown );
	add( 6, UnKnown );
	add( 7, UnKnown );
}

boost::call_traits< Utility::SysLogSeverityType::value_type >::const_reference Utility::SysLogSeverityType::get( boost::call_traits< Utility::SysLogSeverityType::key_type >::const_reference key ) const{
	return map_.at( key );
}

void __fastcall Utility::SysLogSeverityType::add( boost::call_traits< Utility::SysLogSeverityType::key_type >::const_reference key,
											      boost::call_traits< Utility::SysLogSeverityType::value_type >::const_reference value ){
	map_.insert( std::make_pair( key, value ) );
}

bool Utility::SysLogSeverityType::isError( boost::call_traits< Utility::SysLogSeverityType::value_type >::const_reference value ){
	return value == Utility::SysLogSeverityType::Error;
}

bool Utility::SysLogSeverityType::isWarning( boost::call_traits< Utility::SysLogSeverityType::value_type >::const_reference value ){
	return value == Utility::SysLogSeverityType::Warning;
}

bool Utility::SysLogSeverityType::isUnKnown( boost::call_traits< Utility::SysLogSeverityType::value_type >::const_reference value ){
	return value == Utility::SysLogSeverityType::UnKnown;
}
