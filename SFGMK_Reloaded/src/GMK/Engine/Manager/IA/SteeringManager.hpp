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

		r_void registerSteering(gmk::Steering* _steering);
		r_void unregisterSteering(gmk::Steering* _steering);
		r_void cleanSteerings();

		r_void registerSteeringFormation(gmk::SteeringFormation* _formation);
		r_void unregisterSteeringFormation(gmk::SteeringFormation* _formation);
		r_void cleanSteeringFormations();
		gmk::SteeringFormation* getSteeringFormation(r_string _name);

		gmk::vector<gmk::Steering*>& getSteerings();
		gmk::vector<gmk::SteeringFormation*>& getSteeringFormations();

	private:

		SteeringManager();
		~SteeringManager();

		gmk::vector<gmk::Steering*> m_Steerings;
		gmk::vector<gmk::SteeringFormation*> m_Formations;
	};
}

#endif