#include "stdafx.h"
#include "Options.h"
#include "OptionsDecorator.h"

Utility::OptionsDecorator::OptionsDecorator():
		pimpl( new Utility::Options() ){
	int argc( 0 );
	const boost::shared_ptr< LPWSTR >argv( CommandLineToArgvW( GetCommandLine(), &argc ), []( void* const ptr ){ if( ptr ) LocalFree( ptr ); } );
	if ( !argv.get() ) {
		throw std::runtime_error( ( boost::format( "Unable to parse command line %s" ) % boost::system::system_error( GetLastError(), boost::system::get_system_category() ).what() ).str() );
	}

	pimpl->init( argc, argv.get() ); 
}

boost::call_traits< Utility::OptionsDecorator::value_type >::value_type __fastcall Utility::OptionsDecorator::get( boost::call_traits< Utility::OptionsDecorator::key_type >::const_reference key ) const{
	return pimpl->get( key );
}

