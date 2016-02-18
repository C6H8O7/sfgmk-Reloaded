#include "stdafx.h"


namespace gmk
{
	SteeringObstacleAvoidance::SteeringObstacleAvoidance(GameObject* _gameobject)
		: SteeringBehavior(_gameobject),  m_fAheadFactor(STEERING_OBSTACLE_AVOIDANCE_DEFAULT_AHEAD_FACTOR)
	{
	}

	SteeringObstacleAvoidance::~SteeringObstacleAvoidance()
	{
	}


	r_vector2f SteeringObstacleAvoidance::update(r_float _deltaTime)
	{
		sf::FloatRect SpriteRect = ((ComponentSprite*)(m_GameObjectPtr->getComponent("Sprite")))->getSprite()->getGlobalBounds();
		r_float fRadius = MAX(SpriteRect.width, SpriteRect.height);
		r_vector2f position = m_GameObjectPtr->transform.getPosition();
		r_vector2f direction = m_GameObjectPtr->rigidbodyPtr->getDirection();

		double distance = INFINITY;
		double fleeDirection;

		vector<sf::CircleShape*>* Obstacles = ((ComponentShapeContainer*)(m_Target->getComponent("ShapeContainer")))->GetCircles();
		sf::CircleShape* CurrentObstacle(NULL);
		float fCurrentObstacleRadius(0.0f);

		for( unsigned int i(0U); i < Obstacles->size(); i++ )
		{
			CurrentObstacle = (*Obstacles)[i];
			fCurrentObstacleRadius = CurrentObstacle->getRadius();

			r_vector2f positionToObstacle = (CurrentObstacle->getPosition() + r_vector2f(fCurrentObstacleRadius, fCurrentObstacleRadius)) - position;

			// Projection du vecteur positionToObstacle sur le vecteur direction normalisé (r) et son vecteur orthogonal (s)
			double r = positionToObstacle.x * direction.x + positionToObstacle.y * direction.y;
			double s = positionToObstacle.x * direction.y - positionToObstacle.y * direction.x;

			if( r > 0
			   && r - fCurrentObstacleRadius < m_fAheadFactor * math::Calc_Norm(m_GameObjectPtr->rigidbodyPtr->getSpeed()) / m_GameObjectPtr->rigidbodyPtr->getMaxSpeed()
			   && r + fCurrentObstacleRadius < distance
			   && s < (fRadius + fCurrentObstacleRadius)
			   && s > -(fRadius + fCurrentObstacleRadius) ) {
				distance = r - fCurrentObstacleRadius;
				fleeDirection = s;
			}
		}

		if( distance == INFINITY )
			m_Steering.x = m_Steering.y = 0.0f;
		else
		{
			direction *= m_GameObjectPtr->rigidbodyPtr->getMaxForce();
			if( fleeDirection > 0 )
				m_Steering = r_vector2f(-direction.y, direction.x);
			else
				m_Steering = r_vector2f(direction.y, -direction.x);
		}

		return m_Steering;
	}


	const r_float& SteeringObstacleAvoidance::getAheadFactor()
	{
		return m_fAheadFactor;
	}

	r_void SteeringObstacleAvoidance::setAheadFactor(const r_float& _Factor)
	{
		m_fAheadFactor = _Factor;
	}
}