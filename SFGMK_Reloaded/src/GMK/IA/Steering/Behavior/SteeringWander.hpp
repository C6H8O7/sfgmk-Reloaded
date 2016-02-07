/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		08/02/2016
	@brief		Steering behavior

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_WANDER_HPP
#define SFGMKR_STEERING_WANDER_HPP

#include "stdafx.h"


namespace gmk
{
	class SteeringWander : public SteeringBehavior
	{
		public:
			SteeringWander(GameObject* _gameobject);
			~SteeringWander();

			r_vector2f update(r_float _deltaTime) override;
	};
}


#endif