#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		NetClient::NetClient(NetworkManager* _manager)
			: NetActor(_manager, Client), m_threadHostInfosAsk(&NetClient::threadHostInfosAskRoutine, this)
		{
			m_threadHostInfosAsk.launch();
		}

		NetClient::~NetClient()
		{
			m_threadHostInfosAsk.terminate();
		}

		r_void NetClient::send(Packet& _packet)
		{
			if (m_host.isValid())
				m_socket.send(_packet, m_host);
			else if (_packet.isBroadcast())
				sendBroadcast(_packet);
		}

		r_void NetClient::threadHostInfosAskRoutine()
		{
			while (!m_validHost)
			{
				m_packetHandling->sendHostInfos(false);
				sf::sleep(sf::milliseconds(HostDiscoveryTick));
			}
		}

		r_void NetClient::setHost(Address& _address)
		{
			m_host = _address;
			m_validHost = m_host.isValid();
		}

		r_bool NetClient::hasValidHost()
		{
			return m_validHost;
		}
	}
}