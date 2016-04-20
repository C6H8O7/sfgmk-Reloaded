#ifndef SFGMKR_ADDRESS_HPP
#define SFGMKR_ADDRESS_HPP

#include "stdafx.h"

#ifndef SFGMKR_EDITOR

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <WS2tcpip.h>

#endif

namespace gmk
{
	namespace net
	{
		class Address
		{
		public:

			Address();
			Address(r_string _ip, r_uint16 _port);
			Address(const Address& _cpy);
			~Address();

			sockaddr_in getAddress();
			sockaddr_in* getAddressPtr();

			r_int32 getAddressSize();
			r_int32* getAddressSizePtr();

			r_bool isValid();

			static sockaddr_in CreateAddress(r_string _address, r_uint16 _port);

			r_bool operator== (Address& _cmp);

			r_int8* c_str();

		private:

			sockaddr_in m_address;
			r_int32 m_addressSize = sizeof(m_address);
		};
	}
}

#endif