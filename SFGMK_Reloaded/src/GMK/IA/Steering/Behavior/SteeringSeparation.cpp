#include "stdafx.h"


namespace gmk
{
	SteeringSeparation::SteeringSeparation(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_fDistanceMax(STEERING_SEPARATION_DEFAULT_MAX_DISTANCE)
	{
	}


	r_vector2f SteeringSeparation::update(r_float _deltaTime)
	{
		m_Steering.x = m_Steering.y = 0.0f;
		r_vector2f Position = m_GameObjectPtr->transform.getPosition();

		for( r_uint32 i(0U); i < m_Steerings->size(); i++ )
		{
			r_vector2f TargetPos = (*m_Steerings)[i]->getGameObject()->transform.getPosition();

			r_vector2f Repulse = Position - TargetPos;
			r_float fLength = math::Calc_Norm(Repulse);

			if( fLength != 0.0f && fLength < m_fDistanceMax )
			{
				Repulse = Repulse / (fLength * fLength);

				m_Steering += Repulse;
			}
		}
		
		return m_Steering;
	}


	const r_float& SteeringSeparation::getDistanceMax()
	{
		return m_fDistanceMax;
	}

	r_void SteeringSeparation::setDistanceMax(const r_float& _Distance)
	{
		m_fDistanceMax = _Distance;
	}
}