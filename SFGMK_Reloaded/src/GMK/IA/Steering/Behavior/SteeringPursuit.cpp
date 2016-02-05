#include "stdafx.h"


namespace gmk
{
	SteeringPursuit::SteeringPursuit(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), target(NULL), m_fPursuitMaxTime(2.0f)
	{
	}


	r_vector2f SteeringPursuit::update(r_float _deltaTime)
	{
		if( !target )
			return r_vector2f();

		r_float fPursuitEstimatedTime = MIN(m_fPursuitMaxTime, math::Calc_Distance(gameobject->transform.getPosition(), target->transform.getPosition()) / math::Calc_Norm(gameobject->rigidbodyPtr->getSpeed()));
		r_vector2f TargetEstimatedPosition = target->transform.getPosition() + target->rigidbodyPtr->getSpeed() * fPursuitEstimatedTime;

		desiredVelocity = TargetEstimatedPosition - gameobject->transform.getPosition();
		desiredVelocity = math::Calc_UnitVector(desiredVelocity);
		desiredVelocity *= gameobject->rigidbodyPtr->getMaxSpeed();
		steering = desiredVelocity - gameobject->rigidbodyPtr->getSpeed();

		return steering;
	}


	r_void SteeringPursuit::setTarget(GameObject* _target)
	{
		target = _target;
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