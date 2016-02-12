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
	
		/*var circleCenter : Vector3D;
		circleCenter = velocity.clone();
		circleCenter.normalize();
		circleCenter.scaleBy(CIRCLE_DISTANCE);
		//
		// Calculate the displacement force
		var displacement : Vector3D;
		displacement = new Vector3D(0, -1);
		displacement.scaleBy(CIRCLE_RADIUS);
		//
		// Randomly change the vector direction
		// by making it change its current angle
		math::RotateVector(displacement, wanderAngle);
		//
		// Change wanderAngle just a bit, so it
		// won't have the same value in the
		// next game frame.
		wanderAngle += Math.random() * ANGLE_CHANGE - ANGLE_CHANGE * .5;
		//
		// Finally calculate and return the wander force
		var wanderForce : Vector3D;
		wanderForce = circleCenter.add(displacement);
		return wanderForce;*/
	

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