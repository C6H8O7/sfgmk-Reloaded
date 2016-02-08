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
	#define STEERING_WANDER_DEFAULT_CIRCLE_DISTANCE 50.0f
	#define STEERING_WANDER_DEFAULT_CIRCLE_RADIUS 25.0f

	class SteeringWander : public SteeringBehavior
	{
		public:
			SteeringWander(GameObject* _gameobject);
			~SteeringWander();

			r_vector2f update(r_float _deltaTime) override;

			r_void setCircleDistance(const r_float& _Distance);
			r_void setCircleRadius(const r_float& _Radius);
			const r_vector2f& getCircleCenter();

		private:
			r_float m_fCircleDistance;
			r_float m_fCircleRadius;
			r_vector2f m_CircleCenter;
	};
}


#endif