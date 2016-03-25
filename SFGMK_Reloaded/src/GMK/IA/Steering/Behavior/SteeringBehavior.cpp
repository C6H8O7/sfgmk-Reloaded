#include "stdafx.h"

namespace gmk
{
	SteeringBehavior::SteeringBehavior(GameObject* _gameobject)
		: m_GameObjectPtr(_gameobject), m_Target(NULL), m_Steerings(&SteeringManager::GetSingleton()->getSteerings())
	{
	}


	r_void SteeringBehavior::setTarget(GameObject* _Target)
	{
		m_Target = _Target;
	}

	GameObject* SteeringBehavior::getTarget()
	{
		return m_Target;
	}
}