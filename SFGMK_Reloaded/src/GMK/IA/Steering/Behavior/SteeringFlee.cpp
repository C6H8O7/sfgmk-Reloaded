#include "stdafx.h"


namespace gmk
{
	SteeringFlee::SteeringFlee(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), target(NULL)
	{
	}


	r_vector2f SteeringFlee::update(r_float _deltaTime)
	{
		if( !target )
			return r_vector2f();

		desiredVelocity = gameobject->transform.getPosition() - target->transform.getPosition();
		desiredVelocity = math::Calc_UnitVector(desiredVelocity);
		desiredVelocity *= gameobject->rigidbodyPtr->getMaxSpeed();
		steering = desiredVelocity - gameobject->rigidbodyPtr->getSpeed();

		return steering;
	}


	r_void SteeringFlee::setTarget(GameObject* _target)
	{
		target = _target;
	}
}