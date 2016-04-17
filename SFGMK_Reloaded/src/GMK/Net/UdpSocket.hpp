#ifndef SFGMKR_UDPSOCKET_HPP
#define SFGMKR_UDPSOCKET_HPP

namespace gmk
{
	namespace net
	{
		class UdpSocket : public Socket
		{
		public:

			UdpSocket();
			~UdpSocket();

			r_int32 bind(Address& _address);

			r_int32 send(r_int8* _data, r_uint32 _size, Address& _to);
			r_int32 recv(r_int8* _buffer, r_uint32 _size, Address& _from);

			r_int32 send(Packet& _packet, Address& _to);
			r_int32 recv(Packet& _packet, Address& _from);
		};
	}
}

#endif