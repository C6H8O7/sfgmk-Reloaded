/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		04/02/2016
	@brief		Steering behavior, try to reach a moving target using predictive trajectory

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_PURSUIT_HPP
#define SFGMKR_STEERING_PURSUIT_HPP

#include "stdafx.h"


namespace gmk
{
	class SteeringPursuit : public SteeringBehavior
	{
		public:
			SteeringPursuit(GameObject* _gameobject);

			r_vector2f update(r_float _deltaTime) override;

			r_void setTarget(GameObject* _target);
			const float& getPursuitMaxTime();
			r_void setPursuitMaxTime(const float& _Time);

		protected:
			GameObject* target;
			float m_fPursuitMaxTime;
	};
}


#endif