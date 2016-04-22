#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		PacketHandling::PacketHandling(NetworkManager* _manager, NetActor* _actor)
			: m_manager(_manager), m_actor(_actor)
		{

		}

		PacketHandling::~PacketHandling()
		{

		}

		r_void PacketHandling::handle(Packet& _packet)
		{
			_packet.seek(0);

			r_uint8 type = 0;
			_packet.read((r_int8*)&type, sizeof(type));

			switch (type)
			{
			case HostInfos:
				handleHostInfos(_packet);
				break;

			case GameObjectState:
				handleGameObjectState(_packet);
				break;

			case GameObjectUpdates:
				handleGameObjectUpdates(_packet);
				break;

			case ReqGameObjectState:
				handleReqGameOBjectState(_packet);
				break;

			case GameObjectCall:
				handleGameObjectCall(_packet);
				break;
			}
		}

		r_void PacketHandling::handleGameObjectState(Packet& _packet)
		{
			PacketGameObjectState data;
			_packet.read((r_int8*)&data, sizeof(data));

			GameObject* gameobject = m_manager->findNetworkedGameObject(data.update.networkID);

			if (gameobject && data.state == Dead)
			{
				m_manager->unregisterGameObject(gameobject);
				SFMLCanvas::project->getCurrentScene()->removeGameObject(gameobject);
			}

			if (!gameobject && data.state == Alive)
			{
				gameobject = gmk::Factory::getSingleton()->instantiate(data.prefab);

				if (gameobject)
				{
					gameobject->networkPropType = data.prop;

					if (gameobject->networkPropType == GameObjectStateProp::Host && m_actor->getType() == NetActor::Host)
						gameobject->networkProp = 0;
					else
						gameobject->networkProp = 1;

					gameobject->networkID = data.update.networkID;
					
					gameobject->name = data.name;
					gameobject->transform.setPosition(data.update.x, data.update.y);
					gameobject->transform.setScale(data.update.sx, data.update.sy);
					gameobject->transform.setRotation(data.update.rotation);

					ComponentLANReplication* component = (ComponentLANReplication*)gameobject->getComponent("LANReplication");

					if (component)
						component->registerNetwork(false);
				}
			}
		}

		r_void PacketHandling::handleGameObjectUpdate(Packet& _packet)
		{
			PacketGameObjectUpdate data;
			_packet.read((r_int8*)&data, sizeof(data));

			GameObject* gameobject = m_manager->findNetworkedGameObject(data.networkID);

			if (!gameobject)
				sendReqGameOBjectState(data.networkID);

			if (gameobject && gameobject->networkProp)
			{
				gameobject->transform.setPosition(data.x, data.y);
				gameobject->transform.setScale(data.sx, data.sy);
				gameobject->transform.setRotation(data.rotation);
			}
		}

		r_void PacketHandling::handleGameObjectUpdates(Packet& _packet)
		{
			r_uint8 updateCount = 0;
			_packet.read((r_int8*)&updateCount, sizeof(updateCount));

			for (r_uint32 i = 0; i < (r_uint32)updateCount; i++)
				handleGameObjectUpdate(_packet);
		}

		r_void PacketHandling::handleReqGameOBjectState(Packet& _packet)
		{
			PacketReqGameObjectState data;
			_packet.read((r_int8*)&data, sizeof(data));

			GameObject* gameobject = m_manager->findNetworkedGameObject(data.networkID);

			if (gameobject && !gameobject->networkProp)
				m_manager->sendState(gameobject, Alive);
		}

		r_void PacketHandling::handleHostInfos(Packet& _packet)
		{
			PacketHostInfos data;
			_packet.read((r_int8*)&data, sizeof(data));

			if (data.ack && m_actor && m_actor->getType() == NetActor::Client)
			{
				((NetClient*)m_actor)->setHost(_packet.getAddress());
			}
			else if (!data.ack && m_actor && m_actor->getType() == NetActor::Host)
			{
				((NetHost*)m_actor)->registerClient(_packet.getAddress());
				sendHostInfos(true);
			}
		}

		r_void PacketHandling::handleGameObjectCall(Packet& _packet)
		{
			PacketGameObjectCall data;
			_packet.read((r_int8*)&data, sizeof(data));

			GameObject* gameobject = SFMLCanvas::project->getCurrentScene()->findGameObjectByName(data.name);

			if (gameobject)
				gameobject->getScriptByName(data.scriptName).callFunction(data.functionName);
		}

		r_void PacketHandling::sendGameObjectState(GameObject* _gameobject, GameObjectStateState _state)
		{
			PacketGameObjectState data;
			PacketGameObjectUpdate dataUpdate;

			dataUpdate.networkID = _gameobject->networkID;
			
			r_vector2f position = _gameobject->transform.getPosition();
			r_vector2f scale = _gameobject->transform.getScale();
			r_float rotation = _gameobject->transform.getRotation();

			dataUpdate.x = position.x;
			dataUpdate.y = position.y;
			dataUpdate.sx = scale.x;
			dataUpdate.sy = scale.y;
			dataUpdate.rotation = rotation;

			data.update = dataUpdate;
			data.state = _state;
			data.prop = _gameobject->networkPropType;

			strcpy(data.name, _gameobject->name.c_str());
			strcpy(data.prefab, _gameobject->prefabID.c_str());

			Packet packet;

			r_uint8 type = GameObjectState;
			packet.write((r_int8*)&type, sizeof(type));
			packet.write((r_int8*)&data, sizeof(data));

			m_actor->m_out.write(packet);
		}

		r_void PacketHandling::sendGameObjectUpdates(gmk::vector<GameObject*>& _gameobjects)
		{
			r_uint32 gameobjectsByPacket = (Packet::MaxPacketSize - 1) / sizeof(PacketGameObjectUpdate);
			r_uint32 packetCount = _gameobjects.size() / gameobjectsByPacket + 1;

			r_uint32 currentGameObject = 0;
			for (r_uint32 i = 0; i < packetCount; i++)
			{
				Packet packet;

				r_uint8 type = GameObjectUpdates;
				packet.write((r_int8*)&type, sizeof(type));
				
				r_uint32 gameobjectToWrite = _gameobjects.size() - currentGameObject;
				r_uint8 gameobjectCount = gameobjectToWrite > gameobjectsByPacket ? (r_uint8)gameobjectsByPacket : (r_uint8)gameobjectToWrite;
				packet.write((r_int8*)&gameobjectCount, sizeof(gameobjectCount));

				for (r_uint32 j = 0; j < gameobjectsByPacket && currentGameObject < _gameobjects.size(); j++)
				{
					GameObject* gameobject = _gameobjects[currentGameObject++];

					PacketGameObjectUpdate data;

					data.networkID = gameobject->networkID;

					r_vector2f position = gameobject->transform.getPosition();
					r_vector2f scale = gameobject->transform.getScale();
					r_float rotation = gameobject->transform.getRotation();

					data.x = position.x;
					data.y = position.y;
					data.sx = scale.x;
					data.sy = scale.y;
					data.rotation = rotation;
					
					packet.write((r_int8*)&data, sizeof(data));
				}

				m_actor->m_out.write(packet);
			}

			_gameobjects.clear();
		}

		r_void PacketHandling::sendReqGameOBjectState(r_uint32 _networkID)
		{
			PacketReqGameObjectState data;
			data.networkID = _networkID;

			Packet packet;

			r_uint8 type = ReqGameObjectState;
			packet.write((r_int8*)&type, sizeof(type));

			packet.write((r_int8*)&data, sizeof(data));

			m_actor->m_out.write(packet);
		}

		r_void PacketHandling::sendHostInfos(r_bool _ack)
		{
			PacketHostInfos data;
			data.ack = _ack;

			Packet packet;
			packet.setBroadcast(true);

			r_uint8 type = HostInfos;
			packet.write((r_int8*)&type, sizeof(type));

			packet.write((r_int8*)&data, sizeof(data));

			m_actor->m_out.write(packet);
		}

		r_void PacketHandling::sendGameObjectCall(r_string _gameobjectName, r_string _scriptName, r_string _funcName)
		{
			PacketGameObjectCall data;
			strcpy_s(data.name, _gameobjectName.c_str());
			strcpy_s(data.scriptName, _scriptName.c_str());
			strcpy_s(data.functionName, _funcName.c_str());

			Packet packet;

			r_uint8 type = GameObjectCall;
			packet.write((r_int8*)&type, sizeof(type));

			packet.write((r_int8*)&data, sizeof(data));

			m_actor->m_out.write(packet);
		}
	}
}