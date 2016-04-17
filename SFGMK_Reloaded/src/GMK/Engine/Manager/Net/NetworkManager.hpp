#ifndef SFGMKR_NETWORKMANAGER_HPP
#define SFGMKR_NETWORKMANAGER_HPP

#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		class NetworkManager
		{
		friend class PacketHandling;

		public:

			enum
			{
				Port = 1807,
				MaxIO = 256
			};

			static NetworkManager* GetInstance();

			r_void update();

			r_void registerGameObject(GameObject* _gameobject);
			r_void unregisterGameObject(GameObject* _gameobject);

			GameObject* findNetworkedGameObject(r_uint32 _networkID);

			r_void sendUpdate(GameObject* _gameobject);

			r_void clean();

		private:

			NetworkManager();
			~NetworkManager();

			r_void threadNetworkInputRoutine();
			r_void threadNetworkOutputRoutine();

			CircularBuffer<Packet, MaxIO> m_in;
			CircularBuffer<Packet, MaxIO> m_out;

			sf::Thread m_inThread;
			sf::Thread m_outThread;

			r_bool m_terminating = false;

			UdpSocket m_socket;

			gmk::vector<GameObject*> m_networkedGameObjects;
			gmk::vector<GameObject*> m_objectsNeedingUpdate;

			PacketHandling m_packetHandling;
		};
	}
}

#endif