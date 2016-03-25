#include "stdafx.h"

namespace gmk
{
	Steering::Steering(GameObject* _gameobject)
		: m_GameObject(_gameobject), m_SteeringVector(0.0f, 0.0f)
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
			m_SteeringVector.x = m_SteeringVector.y = 0.0f;

			for (r_uint32 i = 0; i < m_Behaviors.size(); i++)
			{
				sSTEERING_BEHAVIOR* sbehavior = m_Behaviors[i];
				m_SteeringVector += sbehavior->behavior->update(_deltaTime) * sbehavior->weight;
			}

			m_GameObject->rigidbodyPtr->addForce(m_SteeringVector);
		}
	}

	r_void Steering::addBehavior(const r_string& _Name, SteeringBehavior* _behavior, r_float _weight)
	{
		m_Behaviors.push_back(new sSTEERING_BEHAVIOR(_Name, _behavior, _weight));
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

	r_float Steering::getBehaviorWeight(SteeringBehavior* _behavior)
	{
		for( r_uint32 i = 0; i < m_Behaviors.size(); i++ )
		{
			sSTEERING_BEHAVIOR* sbehavior = m_Behaviors[i];

			if( sbehavior->behavior == _behavior )
				return sbehavior->weight;
		}

		return 0.0f;
	}

	r_void Steering::cleanBehaviors()
	{
		m_Behaviors.clear();
	}


	const r_vector2f Steering::getSteeringVector()
	{
		return m_SteeringVector;
	}


	GameObject* Steering::getGameObject()
	{
		return m_GameObject;
	}


	r_bool Steering::setSteeringTarget(const r_string& _Steering, GameObject* _Target)
	{
		for( r_uint32 i(0U); i < m_Behaviors.size(); i++ )
		{
			if( m_Behaviors[i]->Name == _Steering )
			{
				m_Behaviors[i]->behavior->setTarget(_Target);
				return true;
			}
		}

		return false;
	}

	r_bool Steering::setSteeringWeight(const r_string& _Steering, r_float _Weight)
	{
		for( r_uint32 i(0U); i < m_Behaviors.size(); i++ )
		{
			if( m_Behaviors[i]->Name == _Steering )
			{
				m_Behaviors[i]->weight = _Weight;
				return true;
			}
		}

		return false;
	}
}