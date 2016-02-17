#include "stdafx.h"


namespace gmk
{
	SteeringPathFollowing::SteeringPathFollowing(GameObject* _gameobject)
		: SteeringBehavior(_gameobject), m_uiCurrentTarget(0U)
	{
	}


	r_vector2f SteeringPathFollowing::update(r_float _deltaTime)
	{
		if( m_Target )
		{
			vector<sf::CircleShape*>* Path = ((ComponentShapeContainer*)(m_Target->getComponent("ShapeContainer")))->GetCircles();
			sf::CircleShape* NextTarget = (*Path)[m_uiCurrentTarget];

			r_float fRadius = NextTarget->getRadius();
			r_vector2f TargetPosition = NextTarget->getPosition() + r_vector2f(fRadius, fRadius);
			r_vector2f Position = m_GameObjectPtr->transform.getPosition();

			if( math::Calc_Distance(Position, TargetPosition) < fRadius )
			{
				m_uiCurrentTarget++;
				if( m_uiCurrentTarget >= Path->size() )
					m_uiCurrentTarget = 0U;
			}

			m_Steering = math::Calc_UnitVector(TargetPosition - Position);
		}

		return m_Steering;
	}
}