#include "stdafx.h"


namespace gmk
{
	SteeringEvasion::SteeringEvasion(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_fEvasionMaxTime(2.0f)
	{
	}


	r_vector2f SteeringEvasion::update(r_float _deltaTime)
	{
		if( !m_Target )
			return r_vector2f();

		r_float fEvasionEstimatedTime = MIN(m_fEvasionMaxTime, math::Calc_Distance(m_GameObjectPtr->transform.getPosition(), m_Target->transform.getPosition()) / math::Calc_Norm(m_GameObjectPtr->rigidbodyPtr->getSpeed()));
		r_vector2f TargetEstimatedPosition = m_Target->transform.getPosition() + m_Target->rigidbodyPtr->getSpeed() * fEvasionEstimatedTime;

		m_DesiredVelocity = m_GameObjectPtr->transform.getPosition() - TargetEstimatedPosition;
		m_DesiredVelocity = math::Calc_UnitVector(m_DesiredVelocity);
		m_DesiredVelocity *= m_GameObjectPtr->rigidbodyPtr->getMaxSpeed();
		m_Steering = m_DesiredVelocity - m_GameObjectPtr->rigidbodyPtr->getSpeed();
		
		return m_Steering;
	}


	const float& SteeringEvasion::getEvasionMaxTime()
	{
		return m_fEvasionMaxTime;
	}

	r_void SteeringEvasion::setEvasionMaxTime(const float& _Time)
	{
		m_fEvasionMaxTime = _Time;
	}
}