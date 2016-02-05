#include "stdafx.h"


namespace gmk
{
	SteeringPursuit::SteeringPursuit(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_fPursuitMaxTime(2.0f)
	{
	}


	r_vector2f SteeringPursuit::update(r_float _deltaTime)
	{
		if( !m_Target )
			return r_vector2f();

		r_float fPursuitEstimatedTime = MIN(m_fPursuitMaxTime, math::Calc_Distance(m_GameObjectPtr->transform.position, m_Target->transform.position) / math::Calc_Norm(m_GameObjectPtr->rigidbodyPtr->getSpeed()));
		r_vector2f TargetEstimatedPosition = m_Target->transform.position + m_Target->rigidbodyPtr->getSpeed() * fPursuitEstimatedTime;

		m_DesiredVelocity = TargetEstimatedPosition - m_GameObjectPtr->transform.position;
		m_DesiredVelocity = math::Calc_UnitVector(m_DesiredVelocity);
		m_DesiredVelocity *= m_GameObjectPtr->rigidbodyPtr->getMaxSpeed();
		m_Steering = m_DesiredVelocity - m_GameObjectPtr->rigidbodyPtr->getSpeed();

		return m_Steering;
	}


	const float& SteeringPursuit::getPursuitMaxTime()
	{
		return m_fPursuitMaxTime;
	}

	r_void SteeringPursuit::setPursuitMaxTime(const float& _Time)
	{
		m_fPursuitMaxTime = _Time;
	}
}