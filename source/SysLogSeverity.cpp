#include "stdafx.h"
#include "SysLogSeverity.h"

Utility::SysLogSeverity::SysLogSeverity()
{
	add( 0, "������ (Emergency): ������� ����������������" );
	add( 1, "������� (Alert): ������� ������� ������������ �������������" );
	add( 2, "����������� (Critical): ��������� ������� �����������" );
	add( 3, "������ (Error): ��������� � ��������� �������" );
	add( 4, "�������������� (Warning): �������������� � ��������� ���������" );
	add( 5, "��������� (Notice): ��������� � ����������, �� ������ ��������" );
	add( 6, "�������������� (Informational): �������������� ���������" );
	add( 7, "������� (Debug): ���������� ���������" );
}

boost::call_traits< Utility::SysLogSeverity::value_type >::const_reference Utility::SysLogSeverity::get( boost::call_traits< Utility::SysLogSeverity::key_type >::const_reference key ) const{
	return map_.at( key );
}

void __fastcall Utility::SysLogSeverity::add( boost::call_traits< Utility::SysLogSeverity::key_type >::const_reference key,
											  boost::call_traits< Utility::SysLogSeverity::value_type >::const_reference value ){
	map_.insert( std::make_pair( key, value ) );
}
