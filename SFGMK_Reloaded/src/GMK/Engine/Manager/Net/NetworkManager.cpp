#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		NetworkManager::NetworkManager()
		{

		}

		NetworkManager::~NetworkManager()
		{
			if (m_actor)
				delete m_actor;
		}

		NetworkManager* NetworkManager::GetInstance()
		{
			static NetworkManager instance;
			return &instance;
		}

		r_void NetworkManager::SetHost()
		{
			GetInstance()->setHost();
		}

		r_void NetworkManager::SetClient()
		{
			GetInstance()->setClient();
		}

		r_int32 NetworkManager::IsHost()
		{
			NetActor* actor = NetworkManager::GetInstance()->m_actor;

			r_int32 result = 0;

			if (actor && actor->getType() == NetActor::Host)
				result = 1;

			return result;
		}

		r_int32 NetworkManager::HasValidHost()
		{
			NetActor* actor = NetworkManager::GetInstance()->m_actor;

			r_int32 result = 0;

			if (actor && actor->getType() == NetActor::Client)
				result = ((NetClient*)actor)->hasValidHost() ? 1 : 0;

			return result;
		}

		r_void NetworkManager::SendGameObjectCall(r_string _gameobjectName, r_string _scriptName, r_string _funcName)
		{
			NetActor* actor = NetworkManager::GetInstance()->m_actor;

			if (actor)
				actor->getPacketHandling().sendGameObjectCall(_gameobjectName, _scriptName, _funcName);
		}

		r_void NetworkManager::Clean()
		{
			NetworkManager* manager = NetworkManager::GetInstance();

			manager->m_shouldClean = true;
		}

		r_void NetworkManager::update()
		{
			if (!m_actor)
				return;

			m_actor->handlePackets();

			if (m_objectsNeedingUpdate.size())
				m_actor->getPacketHandling().sendGameObjectUpdates(m_objectsNeedingUpdate);

			if (m_shouldClean)
			{
				m_shouldClean = false;
				delete m_actor;
				m_actor = 0;
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
			m_objectsNeedingUpdate.removeElement(_gameobject);
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
			if (m_actor)
				m_objectsNeedingUpdate.push_back(_gameobject);
		}

		r_void NetworkManager::sendState(GameObject* _gameobject, PacketHandling::GameObjectStateState _state)
		{
			if (m_actor)
				m_actor->getPacketHandling().sendGameObjectState(_gameobject, _state);
		}

		r_void NetworkManager::clean()
		{
			m_networkedGameObjects.clear();
		}

		r_void NetworkManager::setHost()
		{
			if (m_actor)
				delete m_actor;

			m_actor = new NetHost(this);
		}
		
		r_void NetworkManager::setClient()
		{
			if (m_actor)
				delete m_actor;

			m_actor = new NetClient(this);
		}
	}
}