#ifndef SFGMKR_ADDRESS_HPP
#define SFGMKR_ADDRESS_HPP

#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		class Address
		{
		public:

			Address();
			Address(r_string _ip, r_uint16 _port);
			~Address();

			sockaddr_in getAddress();
			sockaddr_in* getAddressPtr();

			r_int32 getAddressSize();
			r_int32* getAddressSizePtr();

			static sockaddr_in CreateAddress(r_string _address, r_uint16 _port);

		private:

			sockaddr_in m_address;
			r_int32 m_addressSize = sizeof(m_address);
		};
	}
}

#endif