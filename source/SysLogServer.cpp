#include "stdafx.h"
#include "Singleton.h"
#include "Buffer.h"
#include "UdpAsyncServer.h"
#include "UdpAsyncServerDecorator.h"
#include "COMState.h"
#include "COMSessionInitializer.h"
#include "lexical_cast_.h"
#include "Utility.h"

class CSysLogServerModule : public ATL::CAtlServiceModuleT< CSysLogServerModule, IDS_SERVICENAME >
{
public :
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SYSLOG, "{0B23975B-6EA4-4C18-AB52-6710BD92FE23}")
	HRESULT InitializeSecurity() throw()
	{
		return S_OK;
	}

	HRESULT PreMessageLoop (int nShowCmd);
	HRESULT PostMessageLoop();
	void RunMessageLoop (void) throw();
	void OnContinue (void) throw();
	void OnPause (void) throw();
	void OnShutdown (void) throw();
	void OnStop (void) throw();
};

HRESULT CSysLogServerModule::PreMessageLoop (int nShowCmd) throw()
{
	const HRESULT result( ATL::CAtlServiceModuleT< CSysLogServerModule, IDS_SERVICENAME >::PreMessageLoop ( nShowCmd ) );
	if ( SUCCEEDED( result ) ){
		EntryPoint::UdpAsyncServerDecorator& server_udp_514( Memmory::Singleton< EntryPoint::UdpAsyncServerDecorator >::Instance() );
		{
			server_udp_514.run();
		}
	}	
	return result;
}

HRESULT CSysLogServerModule::PostMessageLoop()
{
	EntryPoint::UdpAsyncServerDecorator& server_udp_514( Memmory::Singleton< EntryPoint::UdpAsyncServerDecorator >::Instance() );
	{
		server_udp_514.stop();
	}

    return ATL::CAtlServiceModuleT< CSysLogServerModule, IDS_SERVICENAME >::PostMessageLoop(); 
}

void CSysLogServerModule::RunMessageLoop () throw()
{
   	ATL::CAtlServiceModuleT< CSysLogServerModule, IDS_SERVICENAME >::RunMessageLoop ();
}

void CSysLogServerModule::OnContinue () throw()
{
    ATL::CAtlServiceModuleT< CSysLogServerModule, IDS_SERVICENAME >::OnContinue ();
}

void CSysLogServerModule::OnPause () throw()
{
    ATL::CAtlServiceModuleT< CSysLogServerModule, IDS_SERVICENAME >::OnPause ();
}

void CSysLogServerModule::OnShutdown () throw()
{
    OnStop ();
}

void CSysLogServerModule::OnStop () throw()
{
    ATL::CAtlServiceModuleT< CSysLogServerModule, IDS_SERVICENAME >::OnStop ();
}

CSysLogServerModule _AtlModule;

extern "C" int WINAPI _tWinMain( HINSTANCE /*hInstance*/, 
								 HINSTANCE /*hPrevInstance*/, 
                                 LPTSTR /*lpCmdLine*/, 
								 int nShowCmd ){
	try{
		//setlocale( LC_CTYPE, "Russian" );
		
		COM::COMSessionInitializer& com_session( Memmory::Singleton< COM::COMSessionInitializer >::Instance() );
		if( com_session.isFailed() ){
			_com_issue_error( com_session.getResultCode() );
		}

		const int result( _AtlModule.WinMain( nShowCmd ) );
		if ( result != ERROR_SUCCESS ) {
			throw boost::system::system_error( GetLastError(), boost::system::get_system_category() );
		}

		return result;
	}catch( const _com_error& ce ){
		const std::wstring error_message( 
				boost::lexical_cast< std::wstring >( 
				( boost::format( "main()->source: %s, message: %s, description: %s" ) % ce.Source() % ce.ErrorMessage() % ce.Description() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch( const std::runtime_error& er ){
		const std::wstring error_message( boost::lexical_cast< std::wstring >( ( boost::format( "main()->%s" ) % er.what() ).str() ) );
		Utility::to_error_event_log( error_message );
	}catch(...){
		Utility::to_error_event_log( boost::lexical_cast< std::wstring >( _T("main()->Unknown Error!" ) ) );
	}
	return 1;
}

