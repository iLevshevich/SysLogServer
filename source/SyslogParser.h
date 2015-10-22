#ifndef __SYS_LOG_PARSER_H_INCLUDED__ 
#define __SYS_LOG_PARSER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace Utility{

	template< class T >
	class SyslogParser: 
				private boost::noncopyable{
	public:
		typedef typename boost::call_traits<T>::reference reference;
		typedef typename boost::call_traits<T>::const_reference const_reference;
		typedef typename boost::call_traits<T>::value_type value_type;

		typedef typename T::param_type param_type;
		typedef typename T::result_type result_type;

		explicit SyslogParser( typename boost::call_traits< param_type >::const_reference syslog_data_ ):
						parser( new value_type( syslog_data_ ) ){}

		void parse(){ 
			parser->parse(); 
		}

		typename boost::call_traits< result_type >::const_reference getFacility() const{ 
			return parser->getFacility(); 
		}

        typename boost::call_traits< result_type >::const_reference getSeverity() const{
			return parser->getSeverity(); 
		}

		typename boost::call_traits< result_type >::const_reference getSeverityType() const{
			return parser->getSeverityType();
		}

        typename boost::call_traits< result_type >::const_reference getTimeStamp() const{ 
			return parser->getTimeStamp(); 
		}

        typename boost::call_traits< result_type >::const_reference getHostName() const{ 
			return parser->getHostName(); 
		}

        typename boost::call_traits< result_type >::const_reference getAppName() const{ 
			return parser->getAppName(); 
		}

        typename boost::call_traits< result_type >::const_reference getProcId() const{ 
			return parser->getProcId(); 
		}

        typename boost::call_traits< result_type >::const_reference getMessage() const{ 
			return parser->getMessage();
		}

		typename boost::call_traits< result_type >::const_reference getContent() const{
			return parser->getContent();
		}

	private:
		boost::scoped_ptr< value_type > parser;
	};

};

#pragma pack( pop )

#endif //__SYS_LOG_PARSER_H_INCLUDED__