#ifndef __CONSUMER_COMMAND_H_INCLUDED__ 
#define __CONSUMER_COMMAND_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

#pragma pack( push, 8 )

namespace Command{

	class ConsumerCommand: 
		public Command::ICommand,
		private boost::noncopyable{
	public:
		typedef std::string param_type;
		typedef DataBase::SysLogDAO< DataBase::LogDAO > dao_type;

		explicit ConsumerCommand( boost::call_traits< param_type >::const_reference );
		virtual ~ConsumerCommand();

		virtual void execute();
		void __fastcall setDAO( boost::call_traits< boost::shared_ptr< boost::call_traits< Command::ConsumerCommand::dao_type >::value_type > >::const_reference );
	private:
		bool isSkip( boost::call_traits< Command::ConsumerCommand::param_type >::const_reference ) const;

		boost::call_traits< param_type >::value_type data;
		boost::shared_ptr< boost::call_traits< dao_type >::value_type > dao_ptr;
	};

};

#pragma pack( pop )

#endif //__CONSUMER_COMMAND_H_INCLUDED__