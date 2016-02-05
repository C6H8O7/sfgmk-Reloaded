#include "stdafx.h"


namespace gmk
{
	SteeringEvasion::SteeringEvasion(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), target(NULL), m_fEvasionMaxTime(2.0f)
	{
	}


	r_vector2f SteeringEvasion::update(r_float _deltaTime)
	{
		if( !target )
			return r_vector2f();

		r_float fEvasionEstimatedTime = MIN(m_fEvasionMaxTime, math::Calc_Distance(gameobject->transform.getPosition(), target->transform.getPosition()) / math::Calc_Norm(gameobject->rigidbodyPtr->getSpeed()));
		r_vector2f TargetEstimatedPosition = target->transform.getPosition() + target->rigidbodyPtr->getSpeed() * fEvasionEstimatedTime;

		desiredVelocity = gameobject->transform.getPosition() - TargetEstimatedPosition;
		desiredVelocity = math::Calc_UnitVector(desiredVelocity);
		desiredVelocity *= gameobject->rigidbodyPtr->getMaxSpeed();
		steering = desiredVelocity - gameobject->rigidbodyPtr->getSpeed();

		return steering;
	}


	r_void SteeringEvasion::setTarget(GameObject* _target)
	{
		target = _target;
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