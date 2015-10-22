#include "stdafx.h"
#include "SyslogFacility.h"


Utility::SyslogFacility::SyslogFacility()
{
	add( 0, "Сообщения ядра" );
	add( 1,	"Сообщения пользовательского уровня" );
	add( 2,	"Почтовая система" );
	add( 3,	"Системные службы (daemons)" );
	add( 4,	"Сообщения безопасности/авторизации" );
	add( 5,	"Внутренние сообщения, сгенерированные syslogd" );
	add( 6,	"Подсистема печати" );
	add( 7,	"Подсистема новостных групп (телеконференций, NNTP)" );
	add( 8,	"Подсистема UUCP" );
	add( 9, "Служба времени" );
	add( 10, "Сообщения безопасности/авторизации" );
	add( 11, "Служба FTP" );
	add( 12, "Подсистема NTP" );
	add( 13, "Сообщения аудита" );
	add( 14, "Аварийные сообщения" );
	add( 15, "Служба времени" );
	add( 16, "Локального происхождения 0 (local0)" );
	add( 17, "Локального происхождения 1 (local1)" );
	add( 18, "Локального происхождения 2 (local2)" );
	add( 19, "Локального происхождения 3 (local3)" );
	add( 20, "Локального происхождения 4 (local4)" );
	add( 21, "Локального происхождения 5 (local5)" );
	add( 22, "Локального происхождения 6 (local6)" );
	add( 23, "Локального происхождения 7 (local7)" );
}

boost::call_traits< Utility::SyslogFacility::value_type >::const_reference Utility::SyslogFacility::get( boost::call_traits< Utility::SyslogFacility::key_type >::const_reference key ) const{
	return map_.at( key );
}

void __fastcall Utility::SyslogFacility::add( boost::call_traits< Utility::SyslogFacility::key_type >::const_reference key,
											  boost::call_traits< Utility::SyslogFacility::value_type >::const_reference value ){
	map_.insert( std::make_pair( key, value ) );
}


