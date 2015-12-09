namespace gmk
{
	namespace math
	{
		Curb::Curb(const float& _Duration) : m_fTotalTime(_Duration), m_fCurrentTime(0.0f), m_fTimeRatio(0.0f)
		{
		}

		Curb::~Curb()
		{
			delete[] m_Points;
		}


		const sf::Vector3f* Curb::getPoints()
		{
			return m_Points;
		}

		const sf::Vector3f& Curb::getCurrentPosition()
		{
			return m_CurrentPos;
		}

		const float& Curb::getTotalTime()
		{
			return m_fTotalTime;
		}

		const float& Curb::getCurrentTime()
		{
			return m_fCurrentTime;
		}

		const float& Curb::getTimeRatio()
		{
			return m_fTimeRatio;
		}
	}
}