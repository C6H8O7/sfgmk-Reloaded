#include "stdafx.h"

namespace gmk
{
	SteeringSeek::SteeringSeek(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), target(0)
	{

	}

	r_vector2f SteeringSeek::update(r_float _deltaTime)
	{
		if (!target)
			return r_vector2f();

		desiredVelocity = target->transform.position - gameobject->transform.position;
		desiredVelocity = math::Calc_UnitVector(desiredVelocity);
		desiredVelocity *= gameobject->rigidbodyPtr->getMaxSpeed();
		steering = desiredVelocity - gameobject->rigidbodyPtr->getSpeed();

		return steering;
	}

	r_void SteeringSeek::setTarget(GameObject* _target)
	{
		target = _target;
	}
}