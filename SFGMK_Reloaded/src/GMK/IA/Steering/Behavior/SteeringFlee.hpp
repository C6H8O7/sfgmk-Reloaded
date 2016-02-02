/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		02/02/2016
	@brief		Steering behavior, flee from target

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_FLEE_HPP
#define SFGMKR_STEERING_FLEE_HPP

#include "stdafx.h"


namespace gmk
{
	class SteeringFlee : public SteeringBehavior
	{
		public:
			SteeringFlee(GameObject* _gameobject);

			r_vector2f update(r_float _deltaTime) override;

			r_void setTarget(GameObject* _target);

		protected:
			GameObject* target;
	};
}

#endif