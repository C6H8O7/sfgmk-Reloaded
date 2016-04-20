#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		NetHost::NetHost(NetworkManager* _manager)
			: NetActor(_manager, Host)
		{
			m_socket.bind(NETWORK_BIND_ADDRESS);
		}

		NetHost::~NetHost()
		{

		}

		r_void NetHost::send(Packet& _packet)
		{
			for (r_uint32 i = 0; i < m_clients.size(); i++)
				if (!(m_clients[i] == _packet.getAddress()))
					m_socket.send(_packet, m_clients[i]);
		}

		r_int32 NetHost::findClientIndex(Address& _address)
		{
			for (r_uint32 i = 0; i < m_clients.size(); i++)
				if (m_clients[i] == _address)
					return (r_int32)i;

			return -1;
		}

		r_void NetHost::registerClient(Address& _address)
		{
			if (findClientIndex(_address) < 0)
				m_clients.push_back(_address);
		}

		r_void NetHost::handlePackets()
		{
			while (!m_in.isEmpty())
			{
				Packet packet;
				m_in.read(packet);
				m_out.write(packet);
				m_packetHandling->handle(packet);
			}
		}
	}
}