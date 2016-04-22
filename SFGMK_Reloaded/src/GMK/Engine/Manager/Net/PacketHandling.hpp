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
				HostInfos = 10,

				GameObjectState = 100,
				GameObjectUpdates = 101,

				ReqGameObjectState = 102,

				GameObjectCall = 150
			};

			enum GameObjectStateState
			{
				Alive,
				Dead
			};

			enum GameObjectStateProp
			{
				Instancier,
				Host
			};

			struct PacketGameObjectUpdate
			{
				r_uint32 networkID;
				r_float x, y;
				r_float sx, sy;
				r_float rotation;
			};

			struct PacketGameObjectState
			{
				PacketGameObjectUpdate update;
				GameObjectStateState state;
				GameObjectStateProp prop;
				r_int8 name[20];
				r_int8 prefab[20];
			};

			struct PacketGameObjectCall
			{
				r_int8 name[20];
				r_int8 scriptName[20];
				r_int8 functionName[20];
			};

			struct PacketReqGameObjectState
			{
				r_uint32 networkID;
			};

			struct PacketHostInfos
			{
				r_bool ack;
			};

			PacketHandling(NetworkManager* _manager, NetActor* _actor);
			~PacketHandling();

			r_void handle(Packet& _packet);

			r_void handleGameObjectState(Packet& _packet);
			r_void handleGameObjectUpdate(Packet& _packet);
			r_void handleGameObjectUpdates(Packet& _packet);
			r_void handleReqGameOBjectState(Packet& _packet);
			r_void handleHostInfos(Packet& _packet);
			r_void handleGameObjectCall(Packet& _packet);

			r_void sendGameObjectState(GameObject* _gameobject, GameObjectStateState _state);
			r_void sendGameObjectUpdates(gmk::vector<GameObject*>& _gameobjects);
			r_void sendReqGameOBjectState(r_uint32 _networkID);
			r_void sendHostInfos(r_bool _ack);
			r_void sendGameObjectCall(r_string _gameobjectName, r_string _scriptName, r_string _funcName);

		private:

			NetworkManager* m_manager;
			NetActor* m_actor;
		};
	}
}

#endif