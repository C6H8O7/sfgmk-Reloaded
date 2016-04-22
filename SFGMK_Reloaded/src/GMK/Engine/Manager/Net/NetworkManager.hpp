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
		friend class NetActor;

		public:

			enum
			{
				Port = NETWORK_PORT,
				MaxIO = 256
			};

			static NetworkManager* GetInstance();

			static r_void SetHost();
			static r_void SetClient();
			static r_int32 IsHost();
			static r_int32 HasValidHost();
			static r_void SendGameObjectCall(r_string _gameobjectName, r_string _scriptName, r_string _funcName);
			static r_void Clean();

			r_void update();

			r_void registerGameObject(GameObject* _gameobject);
			r_void unregisterGameObject(GameObject* _gameobject);

			GameObject* findNetworkedGameObject(r_uint32 _networkID);

			r_void sendUpdate(GameObject* _gameobject);
			r_void sendState(GameObject* _gameobject, PacketHandling::GameObjectStateState _state);

			r_void clean();

			r_void setHost();
			r_void setClient();

		private:

			NetworkManager();
			~NetworkManager();

			gmk::vector<GameObject*> m_networkedGameObjects;
			gmk::vector<GameObject*> m_objectsNeedingUpdate;

			NetActor* m_actor = 0;

			r_bool m_shouldClean = false;
		};
	}
}

#endif