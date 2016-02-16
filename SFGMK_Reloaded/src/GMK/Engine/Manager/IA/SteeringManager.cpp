#include "stdafx.h"

namespace gmk
{
	SteeringManager::SteeringManager()
	{

	}

	SteeringManager::~SteeringManager()
	{
		cleanSteerings();
		cleanSteeringFormations();
	}

	SteeringManager* SteeringManager::GetSingleton()
	{
		static SteeringManager singleton;

		return &singleton;
	}

	r_void SteeringManager::update()
	{
		for (r_uint32 i = 0; i < m_Formations.size(); i++)
			m_Formations[i]->update();

		r_float deltaTime = gmk::TimeManager::GetSingleton()->getDeltaTime();

		for (r_uint32 i = 0; i < m_Steerings.size(); i++)
			m_Steerings[i]->update(deltaTime);
	}

	r_void SteeringManager::registerSteering(gmk::Steering* _steering)
	{
		m_Steerings.push_back(_steering);
	}

	r_void SteeringManager::unregisterSteering(gmk::Steering* _steering)
	{
		m_Steerings.removeElement(_steering);
	}

	r_void SteeringManager::cleanSteerings()
	{
		m_Steerings.clear();
	}

	r_void SteeringManager::registerSteeringFormation(gmk::SteeringFormation* _formation)
	{
		m_Formations.push_back(_formation);
	}

	r_void SteeringManager::unregisterSteeringFormation(gmk::SteeringFormation* _formation)
	{
		m_Formations.removeElement(_formation);
	}

	r_void SteeringManager::cleanSteeringFormations()
	{
		m_Formations.clear();
	}

	gmk::SteeringFormation* SteeringManager::getSteeringFormation(r_string _name)
	{
		for (r_uint32 i = 0; i < m_Formations.size(); i++)
			if (m_Formations[i]->getName() == _name)
				return m_Formations[i];

		return 0;
	}

	gmk::vector<gmk::Steering*>& SteeringManager::getSteerings()
	{
		return m_Steerings;
	}

	gmk::vector<gmk::SteeringFormation*>& SteeringManager::getSteeringFormations()
	{
		return m_Formations;
	}
}