/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		16/02/2016
	@brief		Steering behavior

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_SEPARATION_HPP
#define SFGMKR_STEERING_SEPARATION_HPP

#include "stdafx.h"


namespace gmk
{
	#define STEERING_SEPARATION_DEFAULT_MAX_DISTANCE 150.0f

	class SteeringSeparation : public SteeringBehavior
	{
		public:
			SteeringSeparation(GameObject* _gameobject);

			r_vector2f update(r_float _deltaTime) override;

			const r_float& getDistanceMax();
			r_void setDistanceMax(const r_float& _Distance);

		protected:
			r_float m_fDistanceMax;
	};
}


#endif