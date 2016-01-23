#ifndef SFGMKR_STEERINGBEHAVIOR_HPP
#define SFGMKR_STEERINGBEHAVIOR_HPP

#include "stdafx.h"

class GameObject;

namespace gmk
{
	class SteeringBehavior
	{
	public:

		SteeringBehavior(GameObject* _gameobject);

		virtual r_vector2f update(r_float _deltaTime) = 0;

		r_vector2f desiredVelocity;
		r_vector2f steering;

		GameObject* gameobject;
	};
}

#endif