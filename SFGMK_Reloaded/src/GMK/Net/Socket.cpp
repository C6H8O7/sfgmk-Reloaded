#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		Socket::Socket(eSOCKET_TYPE _type)
			: m_type(_type)
		{

		}

		Socket::~Socket()
		{
			close();
		}

		r_void Socket::init()
		{
			if (!m_socket)
			{
				m_socket = socket(AF_INET, m_type == UDP ? SOCK_DGRAM : SOCK_STREAM, 0);

				if (m_type == UDP)
					setBroadcast(true);
				else if (m_type == TCP)
					setNagle(false);
			}
		}

		r_void Socket::close()
		{
			if (m_socket)
			{
				closesocket(m_socket);
				m_socket = 0;
			}
		}

		r_void Socket::setBlocking(r_bool _block)
		{
			m_blocking = _block;
			r_ulong blocking = _block ? 0 : 1;
			ioctlsocket(m_socket, FIONBIO, &blocking);
		}

		r_void Socket::setNagle(r_bool _enabled)
		{
			r_int32 disabled = (!_enabled) ? 1 : 0;
			setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, (r_int8*)&disabled, sizeof(disabled));
		}

		r_void Socket::setBroadcast(r_bool _enabled)
		{
			r_int32 enabled = _enabled ? 1 : 0;
			setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (r_int8*)&enabled, sizeof(enabled));
		}

		r_bool Socket::isBlocking()
		{
			return m_blocking;
		}
		
		SOCKET Socket::getHandle()
		{
			return m_socket;
		}
	}
}