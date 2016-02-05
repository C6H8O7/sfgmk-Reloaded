#include "stdafx.h"

namespace gmk
{
	SteeringSeek::SteeringSeek(GameObject* _gameobject)
		: SteeringBehavior(_gameobject)
	{
	}


	r_vector2f SteeringSeek::update(r_float _deltaTime)
	{
		if( !m_Target )
			return r_vector2f();

		m_DesiredVelocity = m_Target->transform.position - m_GameObjectPtr->transform.position;
		m_DesiredVelocity = math::Calc_UnitVector(m_DesiredVelocity);
		m_DesiredVelocity *= m_GameObjectPtr->rigidbodyPtr->getMaxSpeed();
		m_Steering = m_DesiredVelocity - m_GameObjectPtr->rigidbodyPtr->getSpeed();

		return m_Steering;
	}
}