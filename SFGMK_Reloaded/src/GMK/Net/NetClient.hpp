#ifndef SFGMKR_NETCLIENT_HPP
#define SFGMKR_NETCLIENT_HPP

#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		class NetClient : public NetActor
		{
		public:

			enum
			{
				HostDiscoveryTick = 2000
			};

			NetClient(NetworkManager* _manager);
			virtual ~NetClient();

			r_void send(Packet& _packet);

			r_void threadHostInfosAskRoutine();

			r_void setHost(Address& _address);

			r_bool hasValidHost();

		protected:

			Address m_host;
			r_bool m_validHost = false;

			sf::Thread m_threadHostInfosAsk;
		};
	}
}

#endif