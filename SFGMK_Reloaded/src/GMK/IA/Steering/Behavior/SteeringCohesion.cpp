#include "stdafx.h"


namespace gmk
{
	SteeringCohesion::SteeringCohesion(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_fDistanceMax(STEERING_COHESION_DEFAULT_MAX_DISTANCE)
	{
	}


	r_vector2f SteeringCohesion::update(r_float _deltaTime)
	{
		r_vector2f Position = m_GameObjectPtr->transform.getPosition();
		m_Steering.x = m_Steering.y = 0.0f;
		r_bool bCloseToSomeone = false;
		
		for( r_uint32 i(0U); i < m_Steerings->size(); i++ )
		{
			r_vector2f TargetPos = (*m_Steerings)[i]->getGameObject()->transform.getPosition();

			r_vector2f Repulse;
			Repulse.x = (TargetPos.x - Position.x);
			Repulse.y = (TargetPos.y - Position.y);

			if( Repulse.x != 0 && Repulse.y != 0 && math::Calc_Norm(Repulse) < m_fDistanceMax )
			{
				m_Steering.x += Repulse.x;
				m_Steering.y += Repulse.y;
			}
		}

		return m_Steering;
	}


	const r_float& SteeringCohesion::getDistanceMax()
	{
		return m_fDistanceMax;
	}

	r_void SteeringCohesion::setDistanceMax(const r_float& _Distance)
	{
		m_fDistanceMax = _Distance;
	}
}