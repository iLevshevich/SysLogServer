#include "stdafx.h"
#include "SyslogFacility.h"


Utility::SyslogFacility::SyslogFacility()
{
	add( 0, "��������� ����" );
	add( 1,	"��������� ����������������� ������" );
	add( 2,	"�������� �������" );
	add( 3,	"��������� ������ (daemons)" );
	add( 4,	"��������� ������������/�����������" );
	add( 5,	"���������� ���������, ��������������� syslogd" );
	add( 6,	"���������� ������" );
	add( 7,	"���������� ��������� ����� (���������������, NNTP)" );
	add( 8,	"���������� UUCP" );
	add( 9, "������ �������" );
	add( 10, "��������� ������������/�����������" );
	add( 11, "������ FTP" );
	add( 12, "���������� NTP" );
	add( 13, "��������� ������" );
	add( 14, "��������� ���������" );
	add( 15, "������ �������" );
	add( 16, "���������� ������������� 0 (local0)" );
	add( 17, "���������� ������������� 1 (local1)" );
	add( 18, "���������� ������������� 2 (local2)" );
	add( 19, "���������� ������������� 3 (local3)" );
	add( 20, "���������� ������������� 4 (local4)" );
	add( 21, "���������� ������������� 5 (local5)" );
	add( 22, "���������� ������������� 6 (local6)" );
	add( 23, "���������� ������������� 7 (local7)" );
}

boost::call_traits< Utility::SyslogFacility::value_type >::const_reference Utility::SyslogFacility::get( boost::call_traits< Utility::SyslogFacility::key_type >::const_reference key ) const{
	return map_.at( key );
}

void __fastcall Utility::SyslogFacility::add( boost::call_traits< Utility::SyslogFacility::key_type >::const_reference key,
											  boost::call_traits< Utility::SyslogFacility::value_type >::const_reference value ){
	map_.insert( std::make_pair( key, value ) );
}


