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

			const r_float& getDetectionRange();
			r_void setDetectionRange(const float& _Value);

			const vector<sf::CircleShape*>& getObstacles();
			r_void addObstacle(sf::CircleShape* _Obstacle);
			r_bool removeObstacle(sf::CircleShape* _Obstacle);

		protected:
			r_float m_fDetectionRange;
			vector<sf::CircleShape*> m_Obstacles;
	};
}


#endif