namespace sfgmk
{
	TimeManager::TimeManager() : m_fDeltaTime(0.0f), m_fFactor(0.0f), m_fTotalTime(0.0f)
	{

	}

	TimeManager::~TimeManager()
	{

	}

	void TimeManager::update()
	{
		m_fDeltaTime += m_Clock.restart().asSeconds() * m_fFactor;

		m_fTotalTime += m_fDeltaTime;
	}

	float TimeManager::getDeltaTime()
	{
		return m_fDeltaTime;
	}

	void TimeManager::setFactor(float _factor)
	{
		m_fFactor = _factor;
	}

	float TimeManager::getFactor()
	{
		return m_fFactor;
	}

	float TimeManager::getTotalTime()
	{
		return m_fTotalTime;
	}
}