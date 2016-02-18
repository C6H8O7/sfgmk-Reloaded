/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		05/02/2016
	@brief		Steering behavior, allow entities to avoid obstacles

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_OBSTACLE_AVOIDANCE_HPP
#define SFGMKR_STEERING_OBSTACLE_AVOIDANCE_HPP

#include "stdafx.h"


namespace gmk
{
	#define STEERING_OBSTACLE_AVOIDANCE_DEFAULT_AHEAD_FACTOR 150.0f

	class SteeringObstacleAvoidance : public SteeringBehavior
	{
		public:
			SteeringObstacleAvoidance(GameObject* _gameobject);
			~SteeringObstacleAvoidance();

			r_vector2f update(r_float _deltaTime) override;

			const r_float& getAheadFactor();
			r_void setAheadFactor(const r_float& _Factor);

		protected:
			r_float m_fAheadFactor;
	};
}


#endif