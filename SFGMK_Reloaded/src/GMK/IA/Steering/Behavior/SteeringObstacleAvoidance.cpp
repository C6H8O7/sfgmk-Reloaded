#include "stdafx.h"


namespace gmk
{
	SteeringObstacleAvoidance::SteeringObstacleAvoidance(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_MostThreateningObstacle(NULL), m_fMostThreateningObstacleDistance(0.0)
	{
	}

	SteeringObstacleAvoidance::~SteeringObstacleAvoidance()
	{
	}


	r_vector2f SteeringObstacleAvoidance::update(r_float _deltaTime)
	{
		vector<sf::CircleShape*>* Obstacles = ((ComponentShapeContainer*)(m_Target->getComponent("ShapeContainer")))->GetCircles();

		m_MostThreateningObstacle = NULL;
		m_fMostThreateningObstacleDistance = FLT_MAX;
		sf::CircleShape* CurrentObstacle(NULL);

		r_float fDistance(0.0f);
		r_float fRadius(0.0f);
		r_float fDistances[3];

		r_vector2f Position = m_GameObjectPtr->transform.getPosition();
		r_vector2f Speed = m_GameObjectPtr->rigidbodyPtr->getSpeed();

		//Vecteur de détection
		m_AheadVectors[0] = Position + math::Calc_UnitVector(Speed) * 200.0f/*)*//* * (math::Calc_Norm(Speed) / m_GameObjectPtr->rigidbodyPtr->getMaxSpeed())*/;
		m_AheadVectors[1] = Position + math::Calc_UnitVector(Speed) * 100.0f;

		//Détection obstacle
		for( unsigned int i(0U); i < Obstacles->size(); i++ )
		{
			CurrentObstacle = (*Obstacles)[i];
			r_vector2f ObstaclePosition = CurrentObstacle->getPosition() + r_vector2f(CurrentObstacle->getRadius(), CurrentObstacle->getRadius());

			//Permet de sélectionner l'obstacle le plus proche
			if( (fDistance = math::Calc_Distance(Position, ObstaclePosition)) < m_fMostThreateningObstacleDistance )
			{
				fRadius = CurrentObstacle->getRadius();
			
				fDistances[0] = math::Calc_Distance(m_AheadVectors[0], ObstaclePosition);
				fDistances[1] = math::Calc_Distance(m_AheadVectors[1], ObstaclePosition);
				fDistances[2] = math::Calc_Distance(Position, ObstaclePosition);

				if( fDistances[0] <= fRadius )
				{
					m_MostThreateningObstacle = CurrentObstacle;
					m_fMostThreateningObstacleDistance = fDistance;
					m_Steering = math::Calc_UnitVector(m_AheadVectors[0] - m_MostThreateningObstacle->getPosition());
				}

				else if( fDistances[1] <= fRadius )
				{
					m_MostThreateningObstacle = CurrentObstacle;
					m_fMostThreateningObstacleDistance = fDistance;
					m_Steering = math::Calc_UnitVector(m_AheadVectors[1] - m_MostThreateningObstacle->getPosition());
				}
			
				else if( fDistances[2] <= fRadius )
				{
					m_MostThreateningObstacle = CurrentObstacle;
					m_fMostThreateningObstacleDistance = fDistance;
					m_Steering = math::Calc_UnitVector(Position - m_MostThreateningObstacle->getPosition());
				}
			}
		}

		//Determination vecteur de correction de trajectoire
		if( m_MostThreateningObstacle )
			return m_Steering;
		else
			return r_vector2f();
	}


	const r_vector2f& SteeringObstacleAvoidance::getAhead()
	{
		return m_AheadVectors[0];
	}
}