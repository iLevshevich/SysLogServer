#include "stdafx.h"
#include "Singleton.h"
#include "ICommand.h"
#include "Options.h"
#include "OptionsDecorator.h"
#include "SysLog.h"
#include "SysLogDecorator.h"

EntryPoint::SysLogDecorator::SysLogDecorator():
		pimpl( nullptr ){
	Utility::OptionsDecorator& options( Memmory::Singleton< Utility::OptionsDecorator >::Instance() );
	{
		const std::size_t workers_count( boost::lexical_cast< std::size_t >( options.get( "workers_count" ) ) );
		pimpl = boost::shared_ptr< EntryPoint::SysLog >( new EntryPoint::SysLog( workers_count ) );
	}
}

void EntryPoint::SysLogDecorator::run(){
	pimpl->run();	
}

void EntryPoint::SysLogDecorator::stop(){
	pimpl->stop();
}

void __fastcall EntryPoint::SysLogDecorator::producer( Command::ICommand* const command ){
	pimpl->producer( command );
}