/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		18/02/2016
	@brief		Steering

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_PATH_FOLLOWING_HPP
#define SFGMKR_STEERING_PATH_FOLLOWING_HPP

#include "stdafx.h"


namespace gmk
{
	class SteeringPathFollowing : public SteeringBehavior
	{
		public:
			SteeringPathFollowing(GameObject* _gameobject);

			r_vector2f update(r_float _deltaTime) override;

		protected:
			r_uint32 m_uiCurrentTarget;
	};
}


#endif