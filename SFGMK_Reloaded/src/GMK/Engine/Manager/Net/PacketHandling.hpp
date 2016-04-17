#ifndef SFGMKR_PACKETHANDLING_HPP
#define SFGMKR_PACKETHANDLING_HPP

#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		class NetworkManager;

		class PacketHandling
		{
		public:

			enum PacketType
			{
				GameObjectState = 0,
				GameObjectUpdate = 1
			};

			struct PacketGameObjectUpdate
			{
				r_int8 name[10];
				r_float x, y;
				r_float sx, sy;
				r_float rotation;
				r_int8 prefab[10];
				r_bool isDead;
			};

			PacketHandling(NetworkManager* _manager);
			~PacketHandling();

			r_void handle(Packet& _packet);

			r_void handleGameObjectState(Packet& _packet, r_uint32 _networkID);
			r_void handleGameObjectUpdate(Packet& _packet, r_uint32 _networkID);

			r_void sendGameObjectState(GameObject* _gameobject);
			r_void sendGameObjectUpdate(GameObject* _gameobject);

		private:

			NetworkManager* m_manager;
		};
	}
}

#endif