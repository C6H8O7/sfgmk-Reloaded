#include "stdafx.h"


namespace gmk
{
	SteeringArrival::SteeringArrival(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_fSlowingDistance(100.0f)
	{
	}


	r_vector2f SteeringArrival::update(r_float _deltaTime)
	{
		if( !m_Target )
			return r_vector2f();

		r_float fMaxSpeed = m_GameObjectPtr->rigidbodyPtr->getMaxSpeed();

		r_vector2f TargetOffset = m_Target->transform.position - m_GameObjectPtr->transform.position;
		r_float	fDistance = math::Calc_Norm(TargetOffset);
		r_float fRampedSpeed = fMaxSpeed * (fDistance / m_fSlowingDistance);
		r_float	fClippedSpeed = MIN(fRampedSpeed, fMaxSpeed);

		m_DesiredVelocity = (fClippedSpeed / fDistance) * TargetOffset;
		m_Steering = m_DesiredVelocity - m_GameObjectPtr->rigidbodyPtr->getSpeed();

		return m_Steering;
	}


	const r_float& SteeringArrival::getSlowingDistance()
	{
		return m_fSlowingDistance;
	}

	r_void SteeringArrival::setSlowingDistance(const float& _Value)
	{
		m_fSlowingDistance = _Value;
	}
}