#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		Packet::Packet()
		{
			memset(m_data, 0, MaxPacketSize);
		}

		Packet::~Packet()
		{

		}

		r_int8* Packet::getData()
		{
			return m_data;
		}

		r_uint32 Packet::getSize()
		{
			return m_size;
		}

		r_uint32 Packet::getCapacity()
		{
			return m_capacity;
		}

		r_void Packet::write(r_int8* _data, r_uint32 _size)
		{
			if (m_cursor + _size < MaxPacketSize)
			{
				memcpy(m_data + m_cursor, _data, _size);
				m_size = m_cursor += _size;
			}
		}

		r_void Packet::read(r_int8* _buffer, r_uint32 _size)
		{
			if (m_cursor + _size < MaxPacketSize)
			{
				memcpy(_buffer, m_data + m_cursor, _size);
				m_cursor += _size;
			}
		}

		r_void Packet::seek(r_uint32 _pos)
		{
			if (_pos < MaxPacketSize)
			{
				m_cursor = _pos;
			}
		}
	}
}