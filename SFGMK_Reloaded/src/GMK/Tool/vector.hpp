/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		2015
	@brief		Classe de tableau dynamique

--------------------------------------------------------------------------------------------------*/

#include "stdafx.h"

#ifndef SFGMKR_VECTOR_HPP
#define SFGMKR_VECTOR_HPP

#define GMK_VECTOR_INITIAL_SIZE 32U

namespace gmk
{
	template <typename T>
	class vector
	{
	private:
		T* m_Array;
		r_uint32 m_uiElementNumber;
		r_uint32 m_uiSize;

	public:
		vector() : m_Array(NULL), m_uiElementNumber(0U)
		{
			m_uiSize = GMK_VECTOR_INITIAL_SIZE;
			m_Array = (T*)calloc(1, m_uiSize);
		}

		vector(r_uint32 _size) : m_Array(NULL), m_uiElementNumber(_size)
		{
			m_uiSize = _size;
			m_Array = (T*)calloc(1, m_uiSize);
		}

		~vector()
		{
			if (m_Array)
				free(m_Array);
		}

		T& operator [] (const r_uint32& _Index)
		{
			return m_Array[_Index];
		}

		T* getArray()
		{
			return m_Array;
		}

		r_void print()
		{
			for (r_int32 i(0); i < m_uiElementNumber; i++)
				std::cout << m_Array[i] << std::endl;

			std::cout << std::endl;
		}

		r_void resize(const r_int32& _NewSize)
		{
			m_uiSize = _NewSize;
			m_Array = (T*)realloc(m_Array, m_uiSize);

			if (m_uiSize == 0)
				m_Array = NULL;
		}

		r_bool doubleSize()
		{
			if (!m_uiSize)
				return false;
			else
				m_uiSize = m_uiSize << 1;

			m_Array = (T*)realloc(m_Array, m_uiSize);

			return true;
		}

		const r_uint32& getElementNumber()
		{
			return m_uiElementNumber;
		}

		const r_uint32& size()
		{
			return m_uiElementNumber;
		}

		const r_uint32& getSize()
		{
			return m_uiSize;
		}


		T* findElement(const T& _Element)
		{
			for (r_uint32 i(0U); i < m_uiElementNumber; i++)
			{
				if (m_Array[i] == _Element)
					return &m_Array[i];
			}

			return NULL;
		}

		r_int32 findElementIndex(const T& _Element)
		{
			for (r_uint32 i(0U); i < m_uiElementNumber; i++)
			{
				if (m_Array[i] == _Element)
					return i;
			}

			return -1;
		}

		r_bool swapIndex(const r_uint32& _Index1, const r_uint32& _Index2)
		{
			if (_Index1 > m_uiElementNumber || _Index2 > m_uiElementNumber)
				return false;

			T Temp = m_Array[_Index1];
			m_Array[_Index1] = m_Array[_Index2];
			m_Array[_Index2] = Temp;

			return true;
		}

		r_bool swapElement(const T& _Element1, const T& _Element2)
		{
			r_int32 iIndex1 = findElementIndex(_Element1),
				iIndex2 = findElementIndex(_Element2);

			if (iIndex1 > -1 && iIndex2 > -1)
			{
				swapIndex(iIndex1, iIndex2);
				return true;
			}

			return false;
		}

		r_bool removeElementByIndex(const r_int32& _ElementIndex)
		{
			if (_ElementIndex < 0)
				return false;

			else if (_ElementIndex == 0)
				pop_front();
			else if (_ElementIndex == m_uiElementNumber - 1U)
				pop_back();
			else
			{
				swapIndex(_ElementIndex, m_uiElementNumber - 1U);
				pop_back();
			}

			return true;
		}

		r_bool removeElement(const T& _Element)
		{
			return removeElementByIndex(findElementIndex(_Element));
		}

		r_void erase(const r_uint32& _Begin, const r_uint32& _End)
		{
			const r_uint32 uiSizeToErase = (_End - _Begin) + 1;
			
			for( r_uint32 i(_Begin); i < m_uiElementNumber - 1; i++ )
				m_Array[i] = m_Array[i + uiSizeToErase];

			m_uiElementNumber -= uiSizeToErase;
		}

		r_void sort()
		{
			r_bool bSort(true);

			while (bSort)
			{
				bSort = false;

				for (r_uint32 i(0); i < m_uiElementNumber - 1; i++)
				{
					if (m_Array[i] > m_Array[i + 1])
					{
						bSort = true;
						T temp = m_Array[i];
						m_Array[i] = m_Array[i + 1];
						m_Array[i + 1] = temp;
					}
				}
			}
		}


		r_void push_back(const T& _Element)
		{
			m_uiElementNumber++;
			if ((m_uiElementNumber * sizeof(T)) > m_uiSize)
				doubleSize();

			m_Array[m_uiElementNumber - 1U] = _Element;
		}

		r_bool pop_back()
		{
			if (m_uiElementNumber > 0U)
			{
				m_uiElementNumber--;
				return true;
			}

			return false;
		}

		r_void push_front(const T& _Element)
		{
			m_uiElementNumber++;
			if ((m_uiElementNumber * sizeof(T)) > m_uiSize)
				doubleSize();

			for (r_int32 i(m_uiElementNumber - 1); i > 0; i--)
				m_Array[i] = m_Array[i - 1];

			m_Array[0] = _Element;
		}

		r_bool pop_front()
		{
			if (m_uiElementNumber > 0)
			{
				for (r_uint32 i(0U); i < m_uiElementNumber; i++)
					m_Array[i] = m_Array[i + 1];

				m_uiElementNumber--;
				return true;
			}

			return false;
		}


		r_void clear()
		{
			if (m_uiElementNumber > 0U)
			{
				m_uiElementNumber = 0U;
				resize(GMK_VECTOR_INITIAL_SIZE);
			}
		}

		r_void deleteContent()
		{
			for (r_uint32 i(0U); i < m_uiElementNumber; i++)
			{
				delete m_Array[i];
				m_Array[i] = NULL;
			}

			m_uiElementNumber = 0U;
		}

		r_void deleteAndClear()
		{
			deleteContent();
			clear();
		}
	};
}

#endif