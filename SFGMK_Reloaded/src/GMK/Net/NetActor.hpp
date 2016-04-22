#ifndef SFGMKR_NETACTOR_HPP
#define SFGMKR_NETACTOR_HPP

#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		class NetworkManager;
		class PacketHandling;

		class NetActor
		{
			friend class PacketHandling;

		public:

			enum Type
			{
				None,
				Client,
				Host
			};

			NetActor(NetworkManager* _manager, Type _type);
			virtual ~NetActor();

			virtual r_void send(Packet& _packet) = 0;
			virtual r_void sendBroadcast(Packet& _packet);

			r_uint32 getID();

			Type getType();

			virtual r_void handlePackets();

			PacketHandling& getPacketHandling();

		protected:

			r_void threadNetworkInputRoutine();
			r_void threadNetworkOutputRoutine();

			Type m_type = None;

			r_uint32 m_ID;

			UdpSocket m_socket;
			NetworkManager* m_manager;

			PacketHandling* m_packetHandling = 0;

			r_bool m_terminating = false;

			MyCircularBuffer<Packet, NETWORK_MAXIO> m_in;
			MyCircularBuffer<Packet, NETWORK_MAXIO> m_out;

			sf::Thread m_inThread;
			sf::Thread m_outThread;
		};
	}
}

#endif