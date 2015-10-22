#include "stdafx.h"
#include "COMState.h"
#include "COMSessionInitializer.h"

COM::COMSessionInitializer::COMSessionInitializer():
	COM::COMState(){
	result = ::CoInitialize( nullptr );
}

COM::COMSessionInitializer::~COMSessionInitializer(){
	::CoUninitialize();
}