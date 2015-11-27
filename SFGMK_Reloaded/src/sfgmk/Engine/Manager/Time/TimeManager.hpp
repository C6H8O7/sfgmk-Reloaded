#ifndef SFGMKR_TIMEMANAGER_HPP
#define SFGMKR_TIMEMANAGER_HPP

namespace sfgmk
{
	class TimeManager
	{
	public:

		TimeManager();
		~TimeManager();

		void update();

		float getDeltaTime();

		void setFactor(float _factor);
		float getFactor();

		float getTotalTime();

	private:

		float m_fFactor;
		float m_fDeltaTime;
		float m_fTotalTime;

		sf::Clock m_Clock;
	};
}

#endif