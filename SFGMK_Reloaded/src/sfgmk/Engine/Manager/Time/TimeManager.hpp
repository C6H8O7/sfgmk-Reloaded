#ifndef SFGMKR_TIMEMANAGER_HPP
#define SFGMKR_TIMEMANAGER_HPP

namespace sfgmk
{
	class TimeManager
	{
	public:

		void update();

		float getDeltaTime();

		void setFactor(float _factor);
		float getFactor();

		float getTotalTime();

		static TimeManager* GetSingleton();

		float deltaTime;
		float timeFactor;
		float totalTime;

	private:

		TimeManager();
		~TimeManager();

		sf::Clock m_Clock;
	};
}

#endif