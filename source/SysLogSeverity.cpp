#include "stdafx.h"
#include "SysLogSeverity.h"

Utility::SysLogSeverity::SysLogSeverity()
{
	add( 0, "Авария (Emergency): система неработоспособна" );
	add( 1, "Тревога (Alert): система требует немедленного вмешательства" );
	add( 2, "Критический (Critical): состояние системы критическое" );
	add( 3, "Ошибка (Error): сообщения о возникших ошибках" );
	add( 4, "Предупреждение (Warning): предупреждения о возможных проблемах" );
	add( 5, "Замечание (Notice): сообщения о нормальных, но важных событиях" );
	add( 6, "Информационный (Informational): информационные сообщения" );
	add( 7, "Отладка (Debug): отладочные сообщения" );
}

boost::call_traits< Utility::SysLogSeverity::value_type >::const_reference Utility::SysLogSeverity::get( boost::call_traits< Utility::SysLogSeverity::key_type >::const_reference key ) const{
	return map_.at( key );
}

void __fastcall Utility::SysLogSeverity::add( boost::call_traits< Utility::SysLogSeverity::key_type >::const_reference key,
											  boost::call_traits< Utility::SysLogSeverity::value_type >::const_reference value ){
	map_.insert( std::make_pair( key, value ) );
}
