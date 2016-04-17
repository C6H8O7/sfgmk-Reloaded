#ifndef SFGMKR_CIRCULARBUFFER_HPP
#define SFGMKR_CIRCULARBUFFER_HPP

#include "stdafx.h"

namespace gmk
{
	template <class T, r_uint32 size, r_bool overwrite = true>
	class CircularBuffer
	{
	public:

		CircularBuffer()
		{
			m_buffer = (T*)malloc(sizeof(T) * size);
			m_readMutex.lock();
		}

		~CircularBuffer()
		{
			free((r_void*)m_buffer);
		}

		r_bool write(T& _object)
		{
			r_bool result = false;

			m_mutex.lock();

			if (overwrite || m_writeAhead < size)
			{
				m_buffer[m_writeCursor] = _object;
				incrementCursor(m_writeCursor);
				m_writeAhead++;

				result = true;

				m_readMutex.unlock();
			}

			m_mutex.unlock();

			return result;
		}

		r_bool read(T& _buffer)
		{
			r_bool result = false;

			m_readMutex.lock();
			m_mutex.lock();

			if (m_writeAhead > 0)
			{
				_buffer = m_buffer[m_readCursor];
				incrementCursor(m_readCursor);
				m_writeAhead--;

				result = true;
			}

			m_mutex.unlock();
			m_readMutex.unlock();

			return result;
		}

		r_void incrementCursor(r_uint32& _cursor)
		{
			_cursor = (++_cursor) % size;
		}

		r_bool isEmpty()
		{
			return m_writeAhead == 0;
		}

	private:

		T* m_buffer = 0;

		r_uint32 m_readCursor = 0;
		r_uint32 m_writeCursor = 0;
		r_uint32 m_writeAhead = 0;

		sf::Mutex m_mutex;
		sf::Mutex m_readMutex;
	};
}

#endif