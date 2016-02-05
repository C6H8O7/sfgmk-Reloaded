#include "stdafx.h"


namespace gmk
{
	SteeringObstacleAvoidance::SteeringObstacleAvoidance(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_fDetectionRange(50.0f)
	{
	}

	SteeringObstacleAvoidance::~SteeringObstacleAvoidance()
	{
		m_Obstacles.clear();
	}


	r_vector2f SteeringObstacleAvoidance::update(r_float _deltaTime)
	{
		if( !m_Target )
			return r_vector2f();



		//Detection obstacle


		//Determination vecteur de correction de trajectoire

		//Correction trajectoire
		/*m_DesiredVelocity = m_GameObjectPtr->transform.getPosition() - m_Target->transform.getPosition();
		m_DesiredVelocity = math::Calc_UnitVector(m_DesiredVelocity);
		m_DesiredVelocity *= m_GameObjectPtr->rigidbodyPtr->getMaxSpeed();
		m_Steering = m_DesiredVelocity - m_GameObjectPtr->rigidbodyPtr->getSpeed();*/

		return m_Steering;
	}


	const r_float& SteeringObstacleAvoidance::getDetectionRange()
	{
		return m_fDetectionRange;
	}

	r_void SteeringObstacleAvoidance::setDetectionRange(const float& _Value)
	{
		m_fDetectionRange = _Value;
	}

	const vector<sf::CircleShape*>& SteeringObstacleAvoidance::getObstacles()
	{
		return m_Obstacles;
	}

	r_void SteeringObstacleAvoidance::addObstacle(sf::CircleShape* _Obstacle)
	{
		m_Obstacles.push_back(_Obstacle);
	}

	r_bool SteeringObstacleAvoidance::removeObstacle(sf::CircleShape* _Obstacle)
	{
		m_Obstacles.removeElement(_Obstacle);
	}
}