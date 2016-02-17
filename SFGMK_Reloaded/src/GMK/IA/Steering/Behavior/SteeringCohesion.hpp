/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		17/02/2016
	@brief		Steering cohesion

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_COHESION_HPP
#define SFGMKR_STEERING_COHESION_HPP

#include "stdafx.h"


namespace gmk
{
	#define STEERING_COHESION_DEFAULT_MAX_DISTANCE 150.0f

	class SteeringCohesion : public SteeringBehavior
	{
		public:
			SteeringCohesion(GameObject* _gameobject);

			r_vector2f update(r_float _deltaTime) override;

			const r_float& getDistanceMax();
			r_void setDistanceMax(const r_float& _Distance);

		protected:
			r_float m_fDistanceMax;
	};
}


#endif