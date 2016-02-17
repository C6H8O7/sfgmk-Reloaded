#include "stdafx.h"

namespace gmk
{
	SteeringFormationAgent::SteeringFormationAgent(GameObject* _gameobject)
		: SteeringBehavior(_gameobject)
	{

	}

	r_vector2f SteeringFormationAgent::update(r_float _deltaTime)
	{
		if (!m_FormationName.size())
			return r_vector2f(0.0f, 0.0f);

		gmk::SteeringFormation* formation = gmk::SteeringManager::GetSingleton()->getSteeringFormation(m_FormationName);

		if(!formation)
			return r_vector2f(0.0f, 0.0f);

		r_float max_speed = m_GameObjectPtr->rigidbodyPtr->getMaxSpeed();

		r_vector2f target_pos = formation->getPosition(m_GameObjectPtr);
		r_vector2f target_offset = target_pos - m_GameObjectPtr->transform.getPosition();

		r_float	distance = math::Calc_Norm(target_offset);

		if(distance <= 3.0f)
			return r_vector2f(0.0f, 0.0f);

		r_float ramped_speed = max_speed * (distance / 200.0f);
		r_float	clipped_speed = MIN(ramped_speed, max_speed);

		m_DesiredVelocity = clipped_speed * (target_offset / distance);
		m_Steering = m_DesiredVelocity - m_GameObjectPtr->rigidbodyPtr->getSpeed();

		return m_Steering;
	}

	r_void SteeringFormationAgent::setSteeringFormation(r_string _name)
	{
		m_FormationName = _name;
	}

	r_string SteeringFormationAgent::getSteeringFormation()
	{
		return m_FormationName;
	}
}