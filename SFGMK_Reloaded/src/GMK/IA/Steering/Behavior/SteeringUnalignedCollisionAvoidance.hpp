/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		18/02/2016
	@brief		Steering 

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_UNALIGNED_COLLISION_AVOIDANCE_HPP
#define SFGMKR_STEERING_UNALIGNED_COLLISION_AVOIDANCE_HPP

#include "stdafx.h"


namespace gmk
{
	#define STEERING_UNALIGNED_COLLISION_AVOIDANCE_DEFAULT_MAX_DISTANCE 150.0f

	class SteeringUnalignedCollisionAvoidance : public SteeringBehavior
	{
		public:
			SteeringUnalignedCollisionAvoidance(GameObject* _gameobject);

			r_vector2f update(r_float _deltaTime) override;

			const r_float& getDistanceMax();
			r_void setDistanceMax(const r_float& _Distance);

		protected:
			r_float m_fDetectionDistance;
	};
}


#endif