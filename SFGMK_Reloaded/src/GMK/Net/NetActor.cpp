#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		NetActor::NetActor(NetworkManager* _manager, Type _type)
			: m_manager(_manager), m_type(_type),
			m_inThread(&NetActor::threadNetworkInputRoutine, this), m_outThread(&NetActor::threadNetworkOutputRoutine, this)
		{
			m_ID = NETWORK_RANDOM;

			m_socket.init();
			m_socket.setReuseAddr(true);

			m_inThread.launch();
			m_outThread.launch();

			m_packetHandling = new PacketHandling(m_manager, this);
		}

		NetActor::~NetActor()
		{
			m_terminating = true;

			m_inThread.terminate();
			m_outThread.terminate();

			m_socket.close();

			delete m_packetHandling;
		}

		r_void NetActor::sendBroadcast(Packet& _packet)
		{
			m_socket.send(_packet, NETWORK_BROADCAST_ADDRESS);
		}

		r_uint32 NetActor::getID()
		{
			return m_ID;
		}
		
		r_void NetActor::threadNetworkInputRoutine()
		{
			Packet packet;
			Address from;

			while (!m_terminating)
			{
				if (m_socket.recv(packet, from) >= 0)
					m_in.write(packet);
			}
		}

		r_void NetActor::threadNetworkOutputRoutine()
		{
			Packet packet;

			while (!m_terminating)
			{
				if (m_out.read(packet))
					send(packet);
			}
		}

		NetActor::Type NetActor::getType()
		{
			return m_type;
		}

		r_void NetActor::handlePackets()
		{
			while (!m_in.isEmpty())
			{
				Packet packet;
				m_in.read(packet);
				m_packetHandling->handle(packet);
			}
		}

		PacketHandling& NetActor::getPacketHandling()
		{
			return (*m_packetHandling);
		}
	}
}