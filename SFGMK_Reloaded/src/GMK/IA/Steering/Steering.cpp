#include "stdafx.h"

namespace gmk
{
	Steering::Steering(GameObject* _gameobject)
		: m_GameObject(_gameobject)
	{

	}

	Steering::~Steering()
	{

	}

	r_void Steering::update(r_float _deltaTime)
	{
		r_vector2f dir;

		for (r_uint32 i = 0; i < m_Behaviors.size(); i++)
		{
			sSTEERING_BEHAVIOR* sbehavior = m_Behaviors[i];
			dir += sbehavior->behavior->update(_deltaTime) * sbehavior->weight;
		}

		if (m_GameObject->rigidbodyPtr)
			m_GameObject->rigidbodyPtr->setForce(dir);
	}

	r_void Steering::addBehavior(SteeringBehavior* _behavior, r_float _weight)
	{
		m_Behaviors.push_back(new sSTEERING_BEHAVIOR(_behavior, _weight));
	}

	r_void Steering::cleanBehaviors()
	{
		for (r_uint32 i = 0; i < m_Behaviors.size(); i++)
			delete m_Behaviors[i];

		m_Behaviors.clear();
	}
}