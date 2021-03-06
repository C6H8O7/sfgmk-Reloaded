#ifndef SFGMKR_STEERINGBEHAVIOR_HPP
#define SFGMKR_STEERINGBEHAVIOR_HPP

#include "stdafx.h"

class GameObject;

namespace gmk
{
	class Steering;

	class SteeringBehavior
	{
		public:
			SteeringBehavior(GameObject* _gameobject);

			virtual r_vector2f update(r_float _deltaTime) = 0;

			r_void setTarget(GameObject* _Target);

			GameObject* getTarget();

		protected:

			r_vector2f m_DesiredVelocity;
			r_vector2f m_Steering;

			GameObject* m_GameObjectPtr;
			GameObject* m_Target;

			gmk::vector<Steering*>* m_Steerings;
	};
}

#endif