#ifndef SFGMKR_STEERING_HPP
#define SFGMKR_STEERING_HPP

#include "stdafx.h"

namespace gmk
{
	#define STEERING_DEFAULT_WEIGHT 1.0f

	struct sSTEERING_BEHAVIOR
	{
		r_string Name;
		SteeringBehavior* behavior;
		r_float weight;

		sSTEERING_BEHAVIOR(const r_string& _Name, SteeringBehavior* _behavior = 0, r_float _weight = STEERING_DEFAULT_WEIGHT)
			: Name(_Name), behavior(_behavior), weight(_weight)
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

		r_void addBehavior(const r_string& _Name, SteeringBehavior* _behavior, r_float _weight);
		r_void removeBehavior(SteeringBehavior* _behavior);
		r_void modifyBehaviorWeight(SteeringBehavior* _behavior, r_float _weight);
		r_float getBehaviorWeight(SteeringBehavior* _behavior);
		r_void cleanBehaviors();

		const r_vector2f getSteeringVector();

		GameObject* getGameObject();

		r_bool setSteeringTarget(const r_string& _Steering, GameObject* _Target);
		r_bool setSteeringWeight(const r_string& _Steering, r_float _Weight);

		sSTEERING_BEHAVIOR* getBehavior(SteeringBehavior* _behavior);

	protected:

		GameObject* m_GameObject;

		gmk::vector<sSTEERING_BEHAVIOR*> m_Behaviors;

		r_vector2f m_SteeringVector;
	};
}

#endif