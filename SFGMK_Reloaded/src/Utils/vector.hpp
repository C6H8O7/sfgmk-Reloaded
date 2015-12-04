#ifndef SFGMKR_VECTOR_HPP
#define SFGMKR_VECTOR_HPP

#define GMK_VECTOR_INITIAL_SIZE 32U

namespace sfgmk
{
	template <typename T>
	class vector
	{
	private:
		T* m_Array;
		unsigned int m_uiElementNumber;
		unsigned int m_uiSize;

	public:
		vector() : m_Array(NULL), m_uiElementNumber(0U)
		{
			m_uiSize = GMK_VECTOR_INITIAL_SIZE;
			m_Array = (T*)calloc(1, m_uiSize);
		}

		vector(unsigned int _size) : m_Array(NULL), m_uiElementNumber(_size)
		{
			m_uiSize = _size;
			m_Array = (T*)calloc(1, m_uiSize);
		}

		~vector()
		{
			if (m_Array)
				free(m_Array);
		}

		T& operator [] (const unsigned int& _Index)
		{
			return m_Array[_Index];
		}

		T* getArray()
		{
			return m_Array;
		}

		void print()
		{
			for (int i(0); i < m_uiElementNumber; i++)
				std::cout << m_Array[i] << std::endl;

			std::cout << std::endl;
		}

		void resize(const int& _NewSize)
		{
			m_uiSize = _NewSize;
			m_Array = (T*)realloc(m_Array, m_uiSize);

			if (m_uiSize == 0)
				m_Array = NULL;
		}

		bool doubleSize()
		{
			if (!m_uiSize)
				return false;
			else
				m_uiSize = m_uiSize << 1;

			m_Array = (T*)realloc(m_Array, m_uiSize);

			return true;
		}

		const unsigned int& getElementNumber()
		{
			return m_uiElementNumber;
		}

		const unsigned int& size()
		{
			return m_uiElementNumber;
		}

		const unsigned int& getSize()
		{
			return m_uiSize;
		}


		T* findElement(const T& _Element)
		{
			for (unsigned int i(0U); i < m_uiElementNumber; i++)
			{
				if (m_Array[i] == _Element)
					return &m_Array[i];
			}

			return NULL;
		}

		int findElementIndex(const T& _Element)
		{
			for (unsigned int i(0U); i < m_uiElementNumber; i++)
			{
				if (m_Array[i] == _Element)
					return i;
			}

			return -1;
		}

		bool swapIndex(const unsigned int& _Index1, const unsigned int& _Index2)
		{
			if (_Index1 > m_uiElementNumber || _Index2 > m_uiElementNumber)
				return false;

			T Temp = m_Array[_Index1];
			m_Array[_Index1] = m_Array[_Index2];
			m_Array[_Index2] = Temp;

			return true;
		}

		bool swapElement(const T& _Element1, const T& _Element2)
		{
			int iIndex1 = findElementIndex(_Element1),
				iIndex2 = findElementIndex(_Element2);

			if (iIndex1 > -1 && iIndex2 > -1)
			{
				swapIndex(iIndex1, iIndex2);
				return true;
			}

			return false;
		}

		bool removeElementByIndex(const int& _ElementIndex)
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

		bool removeElement(const T& _Element)
		{
			return removeElementByIndex(findElementIndex(_Element));
		}

		void sort()
		{
			bool bSort(true);

			while (bSort)
			{
				bSort = false;

				for (unsigned int i(0); i < m_uiElementNumber - 1; i++)
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


		void push_back(const T& _Element)
		{
			m_uiElementNumber++;
			if ((m_uiElementNumber * sizeof(T)) > m_uiSize)
				doubleSize();

			m_Array[m_uiElementNumber - 1U] = _Element;
		}

		bool pop_back()
		{
			if (m_uiElementNumber > 0U)
			{
				m_Array[m_uiElementNumber - 1U] = NULL;
				m_uiElementNumber--;
				return true;
			}

			return false;
		}

		void push_front(const T& _Element)
		{
			m_iElementNumber++;
			if ((m_uiElementNumber * sizeof(T)) > m_iSize)
				doubleSize();

			for (int i(m_uiElementNumber - 1); i > 0; i--)
				m_Array[i] = m_Array[i - 1];

			m_Array[0] = _Element;
		}

		bool pop_front()
		{
			if (m_uiElementNumber > 0)
			{
				for (unsigned int i(0U); i < m_uiElementNumber; i++)
					m_Array[i] = m_Array[i + 1];

				m_uiElementNumber--;
				return true;
			}

			return false;
		}


		void clear()
		{
			if (m_uiElementNumber > 0U)
			{
				m_uiElementNumber = 0U;
				resize(GMK_VECTOR_INITIAL_SIZE);
			}
		}

		void deleteContent()
		{
			for (unsigned int i(0U); i < m_uiElementNumber; i++)
			{
				delete m_Array[i];
				m_Array[i] = NULL;
			}

			m_uiElementNumber = 0U;
		}

		void deleteAndClear()
		{
			deleteContent();
			clear();
		}
	};
}

#endif