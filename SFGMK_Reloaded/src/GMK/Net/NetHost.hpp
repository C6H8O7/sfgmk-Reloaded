#ifndef SFGMKR_NETHOST_HPP
#define SFGMKR_NETHOST_HPP

#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		class NetHost : public NetActor
		{
		public:

			NetHost(NetworkManager* _manager);
			virtual ~NetHost();

			r_void send(Packet& _packet);

			r_int32 findClientIndex(Address& _address);
			r_void registerClient(Address& _address);

			virtual r_void handlePackets();

		protected:

			std::vector<Address> m_clients;
		};
	}
}

#endif