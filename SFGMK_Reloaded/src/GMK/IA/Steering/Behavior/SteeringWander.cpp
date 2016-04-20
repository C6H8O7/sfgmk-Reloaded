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
		r_int32 r = rand() % 2000 - 1000;
		r_float angle = (r / 10000.0f);

		m_fWanderAngle += RAND(-1, 1) * m_fRotationSpeed * _deltaTime;

		m_CircleCenter = m_GameObjectPtr->transform.getPosition() + m_GameObjectPtr->rigidbodyPtr->getDirection() * m_fCircleDistance;

		m_WanderForce = m_CircleCenter + r_vector2f(m_fCircleRadius * cosf(m_fWanderAngle), m_fCircleRadius * sinf(m_fWanderAngle)) - m_GameObjectPtr->transform.getPosition();
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