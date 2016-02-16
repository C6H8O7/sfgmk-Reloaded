#ifndef SFGMKR_STEERING_HPP
#define SFGMKR_STEERING_HPP

#include "stdafx.h"

namespace gmk
{
	#define STEERING_DEFAULT_WEIGHT 1.0f

	enum eSTEERING_BEHAVIOR
	{
		STEERING_NONE = 0,
		STEERING_SEEK,
		STEERING_FLEE
	};

	struct sSTEERING_BEHAVIOR
	{
		SteeringBehavior* behavior;
		r_float weight;

		sSTEERING_BEHAVIOR(SteeringBehavior* _behavior = 0, r_float _weight = STEERING_DEFAULT_WEIGHT)
			: behavior(_behavior), weight(_weight)
		{

		}

		~sSTEERING_BEHAVIOR()
		{
			delete behavior;
		}
	};

	class Steering
	{
	public:

		Steering(GameObject* _gameobject);
		~Steering();

		r_void update(r_float _deltaTime);

		r_void addBehavior(SteeringBehavior* _behavior, r_float _weight);
		r_void removeBehavior(SteeringBehavior* _behavior);
		r_void modifyBehaviorWeight(SteeringBehavior* _behavior, r_float _weight);
		r_void cleanBehaviors();

		const r_vector2f getSteeringVector();

		GameObject* getGameObject();

	protected:

		GameObject* m_GameObject;

		gmk::vector<sSTEERING_BEHAVIOR*> m_Behaviors;

		r_vector2f m_SteeringVector;
	};
}

#endif