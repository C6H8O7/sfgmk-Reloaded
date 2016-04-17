#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		PacketHandling::PacketHandling(NetworkManager* _manager)
			: m_manager(_manager)
		{

		}

		PacketHandling::~PacketHandling()
		{

		}

		r_void PacketHandling::handle(Packet& _packet)
		{
			_packet.seek(0);

			r_uint8 type = 0;
			r_uint32 networkID = 0;

			_packet.read((r_int8*)&type, sizeof(type));
			_packet.read((r_int8*)&networkID, sizeof(networkID));

			switch (type)
			{
			case GameObjectState:
				handleGameObjectState(_packet, networkID);
				break;

			case GameObjectUpdate:
				handleGameObjectUpdate(_packet, networkID);
				break;
			}
		}

		r_void PacketHandling::handleGameObjectState(Packet& _packet, r_uint32 _networkID)
		{

		}

		r_void PacketHandling::handleGameObjectUpdate(Packet& _packet, r_uint32 _networkID)
		{
			PacketGameObjectUpdate packet;
			_packet.read((r_int8*)&packet, sizeof(packet));

			GameObject* gameobject = m_manager->findNetworkedGameObject(_networkID);

			if (!gameobject && !packet.isDead)
			{
				gameobject = gmk::Factory::getSingleton()->instantiate(packet.prefab);

				if (gameobject)
				{
					gameobject->networkProp = 1;
					gameobject->networkID = _networkID;
				}
			}

			if (gameobject && gameobject->networkProp)
			{
				gameobject->name = packet.name;
				gameobject->transform.setPosition(packet.x, packet.y);
				gameobject->transform.setScale(packet.sx, packet.sy);
				gameobject->transform.setRotation(packet.rotation);
			}
		}

		r_void PacketHandling::sendGameObjectState(GameObject* _gameobject)
		{

		}

		r_void PacketHandling::sendGameObjectUpdate(GameObject* _gameobject)
		{
			PacketGameObjectUpdate data;

			strcpy(data.name, _gameobject->name.c_str());
			strcpy(data.prefab, _gameobject->prefabID.c_str());

			r_vector2f position = _gameobject->transform.getPosition();
			r_vector2f scale = _gameobject->transform.getScale();
			r_float rotation = _gameobject->transform.getRotation();

			data.isDead = false;

			data.x = position.x;
			data.y = position.y;
			data.sx = scale.x;
			data.sy = scale.y;
			data.rotation = rotation;

			Packet packet;
			r_uint8 type = GameObjectUpdate;
			r_uint32 networkID = _gameobject->networkID;

			packet.write((r_int8*)&type, sizeof(type));
			packet.write((r_int8*)&networkID, sizeof(networkID));
			packet.write((r_int8*)&data, sizeof(data));

			m_manager->m_out.write(packet);
		}
	}
}