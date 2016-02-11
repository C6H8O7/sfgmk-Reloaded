/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		02/02/2016
	@brief		Steering behavior, lead follow a target

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_LEADFOLLOWING_HPP
#define SFGMKR_STEERING_LEADFOLLOWING_HPP

#include "stdafx.h"

namespace gmk
{
	class SteeringLeadFollowing : public SteeringBehavior
	{
		public:
			SteeringLeadFollowing(GameObject* _gameobject);

			r_vector2f update(r_float _deltaTime) override;

		protected:

			r_float m_backDistance = 200.0f;
			r_float m_forwardDistance = 200.0f;
			r_float m_slowingDistance = 200.0f;
	};
}

#endif