#include "stdafx.h"


namespace gmk
{
	SteeringSwarming::SteeringSwarming(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_fAreaRadius(STEERING_SWARMING_DEFAULT_AREA_SIZE)
	{
	}


	r_vector2f SteeringSwarming::update(r_float _deltaTime)
	{
		if ( !m_Target )
			return r_vector2f(0.0f, 0.0f);

		r_vector2f NormalizedVelocity = math::Calc_UnitVector(m_GameObjectPtr->rigidbodyPtr->getSpeed());
		r_vector2f Tangent(-NormalizedVelocity.y, NormalizedVelocity.x);
		r_vector2f TargetDirection = (m_Target->getCenter() - m_GameObjectPtr->transform.getPosition());

		r_float fProjection = TargetDirection.x * NormalizedVelocity.y - TargetDirection.y * NormalizedVelocity.x;

		if( math::Calc_Norm(TargetDirection) > m_fAreaRadius )
		{
			// Increase speed to maximum
			m_Steering = NormalizedVelocity * (m_GameObjectPtr->rigidbodyPtr->getMaxForce());

			float fAngle = math::Calc_Angle(TargetDirection, NormalizedVelocity);
			if( fAngle < 0.1f )
			{
				// Vary the steering as a function of the index of the entity
				double dRandTurn = (RAND(-16, 0) * 0.01f);
				m_Steering += Tangent * (r_float)dRandTurn;
			}
			else
			{
				if( math::IsLeft(TargetDirection, NormalizedVelocity) )
					m_Steering = Tangent * -100.0f;
				else
					m_Steering = Tangent * 100.0f;
			}
		}
		else
		{
			if( fProjection < 0.0f )
				m_Steering = Tangent * 200.0f;
			else
				m_Steering = Tangent * -200.0f;
		}
	
		return m_Steering;
	}


	const r_float& SteeringSwarming::getAreaRadius()
	{
		return m_fAreaRadius;
	}

	r_void SteeringSwarming::setAreaRadius(const r_float& _Radius)
	{
		m_fAreaRadius = _Radius;
	}
}