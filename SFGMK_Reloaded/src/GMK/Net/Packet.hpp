#ifndef SFGMKR_PACKET_HPP
#define SFGMKR_PACKET_HPP

#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		class Packet
		{
		public:

			enum
			{
				MaxPacketSize = 1472
			};

			Packet();
			~Packet();

			r_int8* getData();
			r_uint32 getSize();
			r_uint32 getCapacity();

			r_void write(r_int8* _data, r_uint32 _size);
			r_void read(r_int8* _buffer, r_uint32 _size);

			r_void seek(r_uint32 _pos);

			r_void setAddress(Address& _address);
			Address getAddress();

			r_void setBroadcast(r_bool _broadcast);
			r_bool isBroadcast();

		protected:

			r_int8 m_data[MaxPacketSize];
			r_uint32 m_size = 0;
			r_uint32 m_capacity = MaxPacketSize;

			r_uint32 m_cursor = 0;

			Address m_address;

			r_bool m_broadcast = false;
		};
	}
}

#endif