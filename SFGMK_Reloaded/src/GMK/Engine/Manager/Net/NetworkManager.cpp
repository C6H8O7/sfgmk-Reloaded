#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		NetworkManager::NetworkManager()
			: m_inThread(&NetworkManager::threadNetworkInputRoutine, this), m_outThread(&NetworkManager::threadNetworkOutputRoutine, this),
			  m_packetHandling(this)
		{
			m_socket.init();
			m_socket.bind(Address("0.0.0.0", Port));

			m_inThread.launch();
			m_outThread.launch();
		}

		NetworkManager::~NetworkManager()
		{

		}

		NetworkManager* NetworkManager::GetInstance()
		{
			static NetworkManager instance;
			return &instance;
		}

		r_void NetworkManager::update()
		{
			while (!m_in.isEmpty())
			{
				Packet packet;
				m_in.read(packet);
				m_packetHandling.handle(packet);
			}

			for (r_uint32 i = 0; i < m_objectsNeedingUpdate.size(); i++)
				m_packetHandling.sendGameObjectUpdate(m_objectsNeedingUpdate[i]);
			m_objectsNeedingUpdate.clear();
		}

		r_void NetworkManager::threadNetworkInputRoutine()
		{
			Packet packet;
			Address from;

			while (!m_terminating)
			{
				if (m_socket.recv(packet, from) >= 0)
					m_in.write(packet);
			}
		}

		r_void NetworkManager::threadNetworkOutputRoutine()
		{
			Packet packet;
			Address to("255.255.255.255", Port);

			while (!m_terminating)
			{
				if (m_out.read(packet))
					m_socket.send(packet, to);
			}
		}

		r_void NetworkManager::registerGameObject(GameObject* _gameobject)
		{
			if (m_networkedGameObjects.findElementIndex(_gameobject) < 0)
				m_networkedGameObjects.push_back(_gameobject);
		}

		r_void NetworkManager::unregisterGameObject(GameObject* _gameobject)
		{
			m_networkedGameObjects.removeElement(_gameobject);
		}

		GameObject* NetworkManager::findNetworkedGameObject(r_uint32 _networkID)
		{
			for (r_uint32 i = 0; i < m_networkedGameObjects.size(); i++)
				if (m_networkedGameObjects[i]->networkID == _networkID)
					return m_networkedGameObjects[i];

			return 0;
		}

		r_void NetworkManager::sendUpdate(GameObject* _gameobject)
		{
			m_objectsNeedingUpdate.push_back(_gameobject);
		}

		r_void NetworkManager::clean()
		{
			m_networkedGameObjects.clear();
		}
	}
}