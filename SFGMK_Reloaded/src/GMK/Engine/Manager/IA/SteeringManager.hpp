#ifndef SFGMKR_STEERINGMANAGER_HPP
#define SFGMKR_STEERINGMANAGER_HPP

#include "stdafx.h"

namespace gmk
{
	class SteeringManager
	{
	public:

		static SteeringManager* GetSingleton();

		r_void update();

		r_void registerSteering(Steering* _steering);
		r_void unregisterSteering(Steering* _steering);
		r_void cleanSteerings();

		gmk::vector<Steering*>& getSteerings();

	private:

		SteeringManager();
		~SteeringManager();

		gmk::vector<Steering*> m_Steerings;
	};
}

#endif