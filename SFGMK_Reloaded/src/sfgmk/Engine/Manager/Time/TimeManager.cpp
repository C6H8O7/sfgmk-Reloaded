namespace sfgmk
{
	TimeManager::TimeManager() : deltaTime(0.0f), timeFactor(1.0f), totalTime(0.0f)
	{

	}

	TimeManager::~TimeManager()
	{

	}

	void TimeManager::update()
	{
		deltaTime = m_Clock.restart().asSeconds() * timeFactor;

		totalTime += deltaTime;
	}

	float TimeManager::getDeltaTime()
	{
		return deltaTime;
	}

	void TimeManager::setFactor(float _factor)
	{
		timeFactor = _factor;
	}

	float TimeManager::getFactor()
	{
		return timeFactor;
	}

	float TimeManager::getTotalTime()
	{
		return totalTime;
	}

	TimeManager* TimeManager::GetSingleton()
	{
		static TimeManager singleton;

		return &singleton;
	}
}