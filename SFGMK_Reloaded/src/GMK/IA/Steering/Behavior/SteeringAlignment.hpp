/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		18/02/2016
	@brief		Steering alignment

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_ALIGNMENT_HPP
#define SFGMKR_STEERING_ALIGNMENT_HPP

#include "stdafx.h"


namespace gmk
{
	#define STEERING_ALIGNMENT_DEFAULT_MAX_DISTANCE 150.0f

	class SteeringAlignment : public SteeringBehavior
	{
		public:
			SteeringAlignment(GameObject* _gameobject);

			r_vector2f update(r_float _deltaTime) override;

			const r_float& getDistanceMax();
			r_void setDistanceMax(const r_float& _Distance);

		protected:
			r_float m_fDistanceMax;
	};
}


#endif