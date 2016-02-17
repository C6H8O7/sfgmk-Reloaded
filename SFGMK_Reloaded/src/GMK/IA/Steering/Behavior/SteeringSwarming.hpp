/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		17/02/2016
	@brief		Steering behavior

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_SWARMING_HPP
#define SFGMKR_STEERING_SWARMING_HPP

#include "stdafx.h"


namespace gmk
{
	#define STEERING_SWARMING_DEFAULT_AREA_SIZE 150.0f

	class SteeringSwarming : public SteeringBehavior
	{
		public:
			SteeringSwarming(GameObject* _gameobject);

			r_vector2f update(r_float _deltaTime) override;

			const r_float& getAreaRadius();
			r_void setAreaRadius(const r_float& _Radius);

		protected:
			r_float m_fAreaRadius;
	};
}


#endif