#include "stdafx.h"


namespace gmk
{
	SteeringWander::SteeringWander(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_fCircleDistance(STEERING_WANDER_DEFAULT_CIRCLE_DISTANCE), m_fCircleRadius(STEERING_WANDER_DEFAULT_CIRCLE_RADIUS), m_CircleCenter(0.0f, 0.0f), m_fWanderAngle(0.0f), m_fRotationSpeed(STEERING_WANDER_DEFAULT_ROTATION_SPEED)
	{
	}

	SteeringWander::~SteeringWander()
	{
	}


	r_vector2f SteeringWander::update(r_float _deltaTime)
	{
		m_CircleCenter = m_GameObjectPtr->transform.getPosition() + m_GameObjectPtr->rigidbodyPtr->getDirection() * m_fCircleDistance;
		m_Displacement = r_vector2f(1.0f, 0.0f) * m_fCircleRadius;

		math::RotateVector(m_Displacement, m_fWanderAngle);

		m_fWanderAngle += ((RAND(-1, 1) * m_fRotationSpeed) - (m_fRotationSpeed * 0.5f)) * _deltaTime;
		if( RAND(0, 1) )
			m_fWanderAngle = -m_fWanderAngle;

		m_WanderForce = (m_CircleCenter + m_Displacement) - m_GameObjectPtr->transform.getPosition();
		m_Steering = math::Calc_UnitVector(m_WanderForce);

		return m_Steering;
	}


	r_void SteeringWander::setCircleDistance(const r_float& _Distance)
	{
		m_fCircleDistance = _Distance;
	}

	r_void SteeringWander::setCircleRadius(const r_float& _Radius)
	{
		m_fCircleRadius = _Radius;
	}

	const r_vector2f& SteeringWander::getCircleCenter()
	{
		return m_CircleCenter;
	}
		
	const r_vector2f& SteeringWander::getWanderForce()
	{
		return m_WanderForce;
	}
}