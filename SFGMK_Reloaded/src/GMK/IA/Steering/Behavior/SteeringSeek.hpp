#ifndef SFGMKR_STEERINGSEEK_HPP
#define SFGMKR_STEERINGSEEK_HPP

#include "stdafx.h"

namespace gmk
{
	class SteeringSeek : public SteeringBehavior
	{
	public:

		SteeringSeek(GameObject* _gameobject);

		r_vector2f update(r_float _deltaTime) override;

		r_void setTarget(GameObject* _target);

	protected:

		GameObject* target;
	};
}

#endif