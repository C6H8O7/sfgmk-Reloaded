#include "stdafx.h"


namespace gmk
{
	SteeringUnalignedCollisionAvoidance::SteeringUnalignedCollisionAvoidance(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_fDetectionDistance(STEERING_UNALIGNED_COLLISION_AVOIDANCE_DEFAULT_MAX_DISTANCE)
	{
	}


	r_vector2f SteeringUnalignedCollisionAvoidance::update(r_float _deltaTime)
	{
		m_Steering.x = m_Steering.y = 0.0f;

		r_vector2f Position = m_GameObjectPtr->transform.getPosition();
		r_float Shortest = MAXLONG32;
		r_uint32 uiID = 0U;

		for( r_uint32 i(0U); i < m_Steerings->size(); i++ )
		{
			r_vector2f EntityPosition = (*m_Steerings)[i]->getGameObject()->transform.getPosition();

			if( Position.x != EntityPosition.x && Position.y != EntityPosition.y )
			{
				r_float Distance = math::Calc_Distance(Position, EntityPosition);

				if( Distance < Shortest )
				{
					Shortest = Distance;
					uiID = i;
				}
			}
		}

		if( Shortest <= m_fDetectionDistance )
		{
			r_vector2f OtherNextPos = (*m_Steerings)[uiID]->getGameObject()->transform.getPosition() + (*m_Steerings)[uiID]->getGameObject()->rigidbodyPtr->getSpeed();
			r_vector2f MyNextPos = Position + m_GameObjectPtr->rigidbodyPtr->getSpeed();
			r_vector2f yolo = OtherNextPos - MyNextPos;
			math::Calc_UnitVector(yolo);
			yolo = yolo * -500.0f;
			m_Steering = yolo;
		}

		return m_Steering;
	}


	const r_float& SteeringUnalignedCollisionAvoidance::getDistanceMax()
	{
		return m_fDetectionDistance;
	}

	r_void SteeringUnalignedCollisionAvoidance::setDistanceMax(const r_float& _Distance)
	{
		m_fDetectionDistance = _Distance;
	}
}