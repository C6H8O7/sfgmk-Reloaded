namespace gmk
{
	TimeManager::TimeManager() : deltaTime(0.0f), timeFactor(1.0f), totalTime(0.0f)
	{
#ifdef SFGMKR_EDITOR
		timeFactor = 0.0f;
#endif
	}

	TimeManager::~TimeManager()
	{

	}

	r_void TimeManager::update()
	{
		deltaTime = m_Clock.restart().asSeconds() * timeFactor;

		totalTime += deltaTime;
	}

	r_float TimeManager::getDeltaTime()
	{
		return deltaTime;
	}

	r_void TimeManager::setFactor(r_float _factor)
	{
		timeFactor = _factor;
	}

	r_float TimeManager::getFactor()
	{
		return timeFactor;
	}

	r_float TimeManager::getTotalTime()
	{
		return totalTime;
	}

	TimeManager* TimeManager::GetSingleton()
	{
		static TimeManager singleton;

		return &singleton;
	}
}