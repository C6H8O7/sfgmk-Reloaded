#include "stdafx.h"


namespace gmk
{
	SteeringLeadFollowing::SteeringLeadFollowing(GameObject* _gameobject)
		: SteeringBehavior(_gameobject)
	{

	}

	r_vector2f SteeringLeadFollowing::update(r_float _deltaTime)
	{
		if (!m_Target || !m_Target->rigidbodyPtr)
			return r_vector2f();

		r_vector2f myPos = m_GameObjectPtr->transform.getPosition();

		r_vector2f targetPos = m_Target->transform.getPosition();
		r_vector2f targetDir = m_Target->rigidbodyPtr->getDirection();

		r_vector2f fleePoint = targetPos + targetDir * m_forwardDistance;
		r_vector2f seekPoint = targetPos - targetDir * m_backDistance;

		r_float distanceFleePoint = math::Calc_Distance(myPos, fleePoint);
		r_float distanceSeekPoint = math::Calc_Distance(myPos, seekPoint);

		r_float maxSpeed = m_GameObjectPtr->rigidbodyPtr->getMaxSpeed();

		if (distanceFleePoint <= m_forwardDistance)
		{
			r_vector2f diff = myPos - targetPos;
			r_vector2f perpFleePoint = targetPos + targetDir * (targetDir.x * diff.x + targetDir.y * diff.y);

			m_DesiredVelocity = myPos - perpFleePoint;
			m_DesiredVelocity = math::Calc_UnitVector(m_DesiredVelocity);
			m_DesiredVelocity *= maxSpeed;
		}
		else
		{
			r_float rampedSpeed = maxSpeed * (distanceSeekPoint / m_slowingDistance);
			r_float clippedSpeed = MIN(rampedSpeed, maxSpeed);

			m_DesiredVelocity = (clippedSpeed / distanceSeekPoint) * (seekPoint - myPos);
		}

		m_Steering = m_DesiredVelocity - m_GameObjectPtr->rigidbodyPtr->getSpeed();
		return m_Steering;
	}
}