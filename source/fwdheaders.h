#ifndef __FWDHEADERS_H_INCLUDED__ 
#define __FWDHEADERS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

namespace EntryPoint{
	class UdpAsyncServer;
	class UdpAsyncServerDecorator;
	class SysLog;
	class SysLogDecorator;
	template< class T > class CommandContainer;
};

namespace Memmory{
	template< class T > class Buffer;
	template< class T > class Singleton;
};

namespace Command{
	class ICommand;
	class ConsumerCommand;
};

namespace Utility{
	class Options;
	class OptionsDecorator;
	class SysLogSeverity;
	class SyslogFacility;
	class SysLogSeverityType;
	class QnapParser;
	template< class T > class SyslogParser;
};

namespace COM{
	class COMState;
	class COMSessionInitializer;
};

namespace DataBase{
	class IRepository;
	class BaseRepository;
	class SourceRepository;
	class TypeRepository;
	class MessageRepository;
	class MachineRepository;
	class JournalRepository;
	template< class T > class SysLogDAO;
	class LogDAO;
};

namespace std{
	typedef __int64 __time64_t;
	typedef __time64_t time_t;

	template<class _Elem> struct char_traits;
	template<class _Ty> class allocator;
	template<class _Ty, class _Alloc = allocator<_Ty> > class vector;
	template<class _Ty1, class _Ty2> struct pair;
	template<class _Ty> struct less;
	template<class _Kty, class _Ty, class _Pr = less<_Kty>, class _Alloc = allocator<pair<const _Kty, _Ty> > > class map;
	template<class _Kty, class _Pr = less<_Kty>, class _Alloc = allocator<_Kty> > class set;
	template<class _Elem> struct char_traits;
	template<class _Elem, class _Traits, class _Alloc> class basic_string;
	template<class _Ty, class _Elem = char, class _Traits = char_traits<_Elem> > class ostream_iterator;
	template<class _Elem, class _Byte, class _Statype> class codecvt;
	template<> class codecvt<wchar_t, char, _Mbstatet>;
	typedef basic_string<char ,char_traits<char>, allocator<char> > string;
	typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;
};

namespace boost{
	namespace asio{
		template <typename Protocol> class stream_socket_service;
		template <typename Protocol, typename StreamSocketService = stream_socket_service< Protocol > > class basic_stream_socket;
		class io_service;
		template <typename Allocator> class basic_streambuf;
		typedef basic_streambuf<> streambuf;
		namespace ip{
			class tcp;
			template <typename InternetProtocol> class resolver_service;
			template <typename InternetProtocol> class basic_resolver_iterator;
			template <typename InternetProtocol, typename ResolverService = resolver_service< InternetProtocol > > class basic_resolver;
		};
	};
	
	namespace parameter { 
		struct void_; 
	};

	namespace lockfree {
		template <typename T, class A0 = boost::parameter::void_, class A1 = boost::parameter::void_, class A2 = boost::parameter::void_>class queue;
	};
		
	namespace system{
		class error_code;
		class system_error;
	};

	namespace program_options{
		class variables_map;
	};

	template <typename T> struct call_traits;
	template<class T> class scoped_ptr;
	template<class T> class shared_ptr;
	class condition_variable;
	class mutex;
};

#endif //__FWDHEADERS_H_INCLUDED__