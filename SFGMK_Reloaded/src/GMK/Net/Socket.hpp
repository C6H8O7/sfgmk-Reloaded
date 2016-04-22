#ifndef SFGMKR_SOCKET_HPP
#define SFGMKR_SOCKET_HPP

#include "stdafx.h"

#define NETWORK_RANDOM ((r_uint32)time(0)) ^ ((r_uint32)this)
#define NETWORK_PORT 1807
#define NETWORK_MAXIO 256
#define NETWORK_BROADCAST_ADDRESS gmk::net::Address("255.255.255.255", NETWORK_PORT)
#define NETWORK_BIND_ADDRESS gmk::net::Address("0.0.0.0", NETWORK_PORT)

namespace gmk
{
	namespace net
	{
		class Socket
		{
		public:

			enum eSOCKET_TYPE
			{
				UDP,
				TCP
			};

			Socket(eSOCKET_TYPE _type);
			virtual ~Socket();

			r_void init();
			r_void close();

			r_void setBlocking(r_bool _block);
			r_void setNagle(r_bool _enabled);
			r_void setBroadcast(r_bool _enabled);
			r_void setReuseAddr(r_bool _enabled);

			r_bool isBlocking();
			SOCKET getHandle();

		protected:

			SOCKET m_socket = 0;
			eSOCKET_TYPE m_type;
			r_bool m_blocking = false;
		};

		struct WSAInitializer
		{
			WSAInitializer()
			{
				WSAStartup(MAKEWORD(2, 2), &wsa);
			}

			~WSAInitializer()
			{
				WSACleanup();
			}

			WSADATA wsa;
		};

		WSAInitializer WSAGlobal;
	}
}

#endif