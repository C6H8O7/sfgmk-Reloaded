#include "stdafx.h"


namespace gmk
{
	SteeringWander::SteeringWander(GameObject* _gameobject)
		: SteeringBehavior(_gameobject)
	{
	}

	SteeringWander::~SteeringWander()
	{
	}


	r_vector2f SteeringWander::update(r_float _deltaTime)
	{
		return r_vector2f();
	}
}