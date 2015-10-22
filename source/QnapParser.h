#ifndef __QNAP_PARSER_H_INCLUDED__ 
#define __QNAP_PARSER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace Utility{

	class QnapParser: 
		private boost::noncopyable{
	public:
		typedef std::string param_type;
		typedef std::string result_type;

		explicit QnapParser( boost::call_traits< param_type >::const_reference );

		void parse();

		boost::call_traits< result_type >::const_reference getFacility() const{
			return facility;
		}

		std::size_t getFacilityLevel() const{
			return facility_level;
		}

		boost::call_traits< result_type >::const_reference getSeverity() const{
			return severity;
		}

		boost::call_traits< result_type >::const_reference getSeverityType() const{
			return severity_type;
		}

        std::size_t getSeverityLevel() const{
			return severity_level;
		}

        boost::call_traits< result_type >::const_reference getTimeStamp() const{
			return time_stamp;
		}

        boost::call_traits< result_type >::const_reference getHostName() const{
			return host_name;
		}

        boost::call_traits< result_type >::const_reference getAppName() const{
			return app_name;
		}

        boost::call_traits< result_type >::const_reference getProcId() const{
			return proc_id;
		}

        boost::call_traits< result_type >::const_reference getMessage() const{
			return message;
		}

		boost::call_traits< result_type >::const_reference getContent() const{
			return content;
		}

	private:
		param_type parse_data;

		result_type facility;
		std::size_t facility_level;
		result_type severity;
		std::size_t severity_level;
		result_type severity_type;
		result_type time_stamp;
		result_type host_name;
		result_type app_name;
		result_type proc_id;
		result_type message;
		result_type content;

		static Utility::SysLogSeverity severity_map;
		static Utility::SysLogSeverityType severity_type_map;
	    static Utility::SyslogFacility facility_map;

		const param_type::value_type SP;
		const param_type::value_type PRI_START;
		const param_type::value_type PRI_END;
		const param_type::value_type SD_START;
		const param_type::value_type SD_END;

		const param_type MS_CTX;
		const param_type CN_CTX;
	};

};

#pragma pack( pop )

#endif //__QNAP_PARSER_H_INCLUDED__
