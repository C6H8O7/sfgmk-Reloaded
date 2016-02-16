#include "stdafx.h"

namespace gmk
{
	SteeringManager::SteeringManager()
	{

	}

	SteeringManager::~SteeringManager()
	{
		cleanSteerings();
	}

	SteeringManager* SteeringManager::GetSingleton()
	{
		static SteeringManager singleton;

		return &singleton;
	}

	r_void SteeringManager::update(r_float _deltaTime)
	{
		for (r_uint32 i = 0; i < m_Steerings.size(); i++)
			m_Steerings[i]->update(_deltaTime);
	}

	r_void SteeringManager::registerSteering(Steering* _steering)
	{
		m_Steerings.push_back(_steering);
	}

	r_void SteeringManager::unregisterSteering(Steering* _steering)
	{
		m_Steerings.removeElement(_steering);
	}

	r_void SteeringManager::cleanSteerings()
	{
		m_Steerings.clear();
	}


	gmk::vector<Steering*>& SteeringManager::getSteerings()
	{
		return m_Steerings;
	}
}