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
	class SteeringObstacleAvoidance : public SteeringBehavior
	{
		public:
			SteeringObstacleAvoidance(GameObject* _gameobject);
			~SteeringObstacleAvoidance();

			r_vector2f update(r_float _deltaTime) override;

			const r_vector2f& getAhead();

		protected:
			r_vector2f m_AheadVectors[2];
			sf::CircleShape* m_MostThreateningObstacle;
			r_float m_fMostThreateningObstacleDistance;
	};
}


#endif