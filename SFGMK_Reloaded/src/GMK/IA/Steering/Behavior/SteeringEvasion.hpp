/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		04/02/2016
	@brief		Steering behavior

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_STEERING_EVASION_HPP
#define SFGMKR_STEERING_EVASION_HPP

#include "stdafx.h"


namespace gmk
{
	class SteeringEvasion : public SteeringBehavior
	{
		public:
			SteeringEvasion(GameObject* _gameobject);

			r_vector2f update(r_float _deltaTime) override;

			const float& getEvasionMaxTime();
			r_void setEvasionMaxTime(const float& _Time);

		protected:
			float m_fEvasionMaxTime;
	};
}


#endif