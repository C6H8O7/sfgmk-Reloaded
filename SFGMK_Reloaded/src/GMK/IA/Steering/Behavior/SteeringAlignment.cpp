#include "stdafx.h"


namespace gmk
{
	SteeringAlignment::SteeringAlignment(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_fDistanceMax(STEERING_ALIGNMENT_DEFAULT_MAX_DISTANCE)
	{
	}


	r_vector2f SteeringAlignment::update(r_float _deltaTime)
	{
		r_vector2f Position = m_GameObjectPtr->transform.getPosition();
		r_vector2f Result(0.0f, 0.0f);
		r_vector2f Distance;
		for( r_uint32 i(0U); i < m_Steerings->size(); i++ )
		{
			Distance = (*m_Steerings)[i]->getGameObject()->transform.getPosition() - Position;
			if( math::Calc_Norm(Distance) <= m_fDistanceMax )
				Result += (*m_Steerings)[i]->getGameObject()->rigidbodyPtr->getSpeed();
		}

		r_float fMagnitude = math::Calc_Norm(m_GameObjectPtr->rigidbodyPtr->getSpeed());
		r_vector2f Direction = Result - m_GameObjectPtr->rigidbodyPtr->getSpeed();
		math::Calc_UnitVector(Direction);

		m_Steering = Direction * fMagnitude;

		return m_Steering;
	}


	const r_float& SteeringAlignment::getDistanceMax()
	{
		return m_fDistanceMax;
	}

	r_void SteeringAlignment::setDistanceMax(const r_float& _Distance)
	{
		m_fDistanceMax = _Distance;
	}
}