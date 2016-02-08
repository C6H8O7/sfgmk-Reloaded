#include "stdafx.h"


namespace gmk
{
	SteeringWander::SteeringWander(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_fCircleDistance(STEERING_WANDER_DEFAULT_CIRCLE_DISTANCE), m_fCircleRadius(STEERING_WANDER_DEFAULT_CIRCLE_RADIUS), m_CircleCenter(0.0f, 0.0f)
	{
	}

	SteeringWander::~SteeringWander()
	{
	}


	r_vector2f SteeringWander::update(r_float _deltaTime)
	{
		return r_vector2f();
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
}