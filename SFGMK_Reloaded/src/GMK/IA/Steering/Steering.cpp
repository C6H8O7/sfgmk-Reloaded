#include "stdafx.h"

namespace gmk
{
	Steering::Steering(GameObject* _gameobject)
		: m_GameObject(_gameobject)
	{
		gmk::SteeringManager::GetSingleton()->registerSteering(this);
	}

	Steering::~Steering()
	{
		gmk::SteeringManager::GetSingleton()->unregisterSteering(this);

		cleanBehaviors();
	}

	r_void Steering::update(r_float _deltaTime)
	{
		if (m_GameObject->rigidbodyPtr)
		{
			r_vector2f dir;

			for (r_uint32 i = 0; i < m_Behaviors.size(); i++)
			{
				sSTEERING_BEHAVIOR* sbehavior = m_Behaviors[i];
				dir += sbehavior->behavior->update(_deltaTime) * sbehavior->weight;
			}

			m_GameObject->rigidbodyPtr->addForce(dir);
		}
	}

	r_void Steering::addBehavior(SteeringBehavior* _behavior, r_float _weight)
	{
		m_Behaviors.push_back(new sSTEERING_BEHAVIOR(_behavior, _weight));
	}

	r_void Steering::removeBehavior(SteeringBehavior* _behavior)
	{
		for (r_int32 i = (r_int32)m_Behaviors.size() - 1; i >= 0; i--)
		{
			sSTEERING_BEHAVIOR* sbehavior = m_Behaviors[i];

			if (sbehavior->behavior == _behavior)
				m_Behaviors.removeElementByIndex(i);
		}
	}

	r_void Steering::modifyBehaviorWeight(SteeringBehavior* _behavior, r_float _weight)
	{
		for (r_uint32 i = 0; i < m_Behaviors.size(); i++)
		{
			sSTEERING_BEHAVIOR* sbehavior = m_Behaviors[i];

			if (sbehavior->behavior == _behavior)
				sbehavior->weight = _weight;
		}
	}

	r_void Steering::cleanBehaviors()
	{
		m_Behaviors.clear();
	}
}