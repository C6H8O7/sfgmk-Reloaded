#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		UdpSocket::UdpSocket()
			: Socket(UDP)
		{

		}

		UdpSocket::~UdpSocket()
		{

		}

		r_int32 UdpSocket::bind(Address& _address)
		{
			init();

			return ::bind(m_socket, (const sockaddr*)_address.getAddressPtr(), _address.getAddressSize());
		}

		r_int32 UdpSocket::send(r_int8* _data, r_uint32 _size, Address& _to)
		{
			init();

			if (_size > Packet::MaxPacketSize)
				return 0;

			return ::sendto(m_socket, _data, _size, 0, (const sockaddr*)_to.getAddressPtr(), _to.getAddressSize());
		}

		r_int32 UdpSocket::recv(r_int8* _buffer, r_uint32 _size, Address& _from)
		{
			init();

			if (_size > Packet::MaxPacketSize)
				return 0;

			return ::recvfrom(m_socket, _buffer, _size, 0, (sockaddr*)_from.getAddressPtr(), _from.getAddressSizePtr());
		}

		r_int32 UdpSocket::send(Packet& _packet, Address& _to)
		{
			return send(_packet.getData(), _packet.getSize(), _to);
		}

		r_int32 UdpSocket::recv(Packet& _packet, Address& _from)
		{
			return recv(_packet.getData(), _packet.getCapacity(), _from);
		}
	}
}