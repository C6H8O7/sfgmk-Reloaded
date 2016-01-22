#ifndef SFGMKR_STEERINGBEHAVIOR_HPP
#define SFGMKR_STEERINGBEHAVIOR_HPP

#include "stdafx.h"

namespace gmk
{
	class SteeringBehavior
	{
	public:

		SteeringBehavior();
		~SteeringBehavior();

		virtual r_vector2f update(r_float _deltaTime) = 0;
	};
}

#endif