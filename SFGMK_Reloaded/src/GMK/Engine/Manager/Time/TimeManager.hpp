#ifndef SFGMKR_TIMEMANAGER_HPP
#define SFGMKR_TIMEMANAGER_HPP

#include "stdafx.h"

namespace gmk
{
	class TimeManager
	{
	public:

		r_void update();

		r_float getDeltaTime();
		r_void resetDeltaTime();

		r_void setFactor(r_float _factor);
		r_float getFactor();

		r_float getTotalTime();

		static TimeManager* GetSingleton();

		r_float deltaTime;
		r_float timeFactor;
		r_float totalTime;

	private:

		TimeManager();
		~TimeManager();

		sf::Clock m_Clock;
	};
}

#endif