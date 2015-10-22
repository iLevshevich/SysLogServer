#ifndef __COM_STATE_H_INCLUDED__ 
#define __COM_STATE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace COM{

	class COMState:
		private boost::noncopyable{
	public:
		typedef HRESULT value_type;
		typedef HRESULT return_type;

		COMState();

		bool isSuccess() const;
		bool isFailed() const;

		boost::call_traits< return_type >::value_type getResultCode() const;
	protected:
		HRESULT result;
	};

};

#pragma pack( pop )

#endif //__COM_STATE_H_INCLUDED__


