#ifndef __COM_SESSION_INITIALIZER_H_INCLUDED__ 
#define __COM_SESSION_INITIALIZER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace COM{

	class COMSessionInitializer:
		public COM::COMState{
	public:
		COMSessionInitializer();
		~COMSessionInitializer();
	};

};

#pragma pack( pop )

#endif //__COM_SESSION_INITIALIZER_H_INCLUDED__