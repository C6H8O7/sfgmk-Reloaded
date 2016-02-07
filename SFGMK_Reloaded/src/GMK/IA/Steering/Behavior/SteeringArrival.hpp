/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		05/02/2016
	@brief		Steering behavior, similar to seek but with linear speed reduction

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_ARRIVAL_HPP
#define SFGMKR_STEERING_ARRIVAL_HPP

#include "stdafx.h"


namespace gmk
{
	#define STEERING_ARRIVAL_DEFAULT_SLOWING_DISTANCE 100.0f

	class SteeringArrival : public SteeringBehavior
	{
		public:
			SteeringArrival(GameObject* _gameobject);

			r_vector2f update(r_float _deltaTime) override;

			const r_float& getSlowingDistance();
			r_void setSlowingDistance(const float& _Value);

		protected:
			r_float m_fSlowingDistance;
	};
}


#endif