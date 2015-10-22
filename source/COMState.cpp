#include "stdafx.h"
#include "COMState.h"

COM::COMState::COMState():
	result( S_OK ){}

bool COM::COMState::isSuccess() const{
	return SUCCEEDED(result);
}

bool COM::COMState::isFailed() const{
	return FAILED(result);
}

boost::call_traits< COM::COMState::return_type >::value_type COM::COMState::getResultCode() const{
	return result;
}

//#define S_OK ((HRESULT)0L)
//#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)
//#define FAILED(hr) (((HRESULT)(hr)) < 0)