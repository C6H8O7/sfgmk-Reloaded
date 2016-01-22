#include "stdafx.h"

namespace gmk
{
	SteeringSeek::SteeringSeek(GameObject* _gameobject, GameObject* _target)
		: SteeringBehavior(_gameobject), target(_target)
	{

	}

	r_vector2f SteeringSeek::update(r_float _deltaTime)
	{
		desiredVelocity = target->transform.position - gameobject->transform.position;
		desiredVelocity.normalise() *= gameobject->rigidbodyPtr->getMaxSpeed();
		steering = desiredVelocity - gameobject->rigidbodyPtr->getSpeed();
		return steering;
	}
}