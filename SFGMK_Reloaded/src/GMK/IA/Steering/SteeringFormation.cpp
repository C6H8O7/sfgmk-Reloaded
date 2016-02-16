#include "stdafx.h"

namespace gmk
{
	SteeringFormation::SteeringFormation()
	{
		gmk::SteeringManager::GetSingleton()->registerSteeringFormation(this);
	}

	SteeringFormation::~SteeringFormation()
	{
		gmk::SteeringManager::GetSingleton()->unregisterSteeringFormation(this);
	}

	r_void SteeringFormation::update()
	{
		m_CurrentPositionIndex = 0;
	}

	r_vector2f SteeringFormation::getPosition(GameObject* _unit)
	{
		r_vector2f unit_position = _unit->transform.getPosition();

		if (!m_Leader)
			return unit_position;

		r_float index = (r_float)m_CurrentPositionIndex++;

		r_float angle = 2.0f * PI / 20.0f;

		r_vector2f position = m_Leader->transform.getPosition();

		position.x += 200.0f * cosf(angle * index);
		position.y += 200.0f * sinf(angle * index);

		return position;
	}

	r_void SteeringFormation::setLeader(GameObject* _leader)
	{
		m_Leader = _leader;
	}

	GameObject* SteeringFormation::getLeader()
	{
		return m_Leader;
	}

	r_void SteeringFormation::setName(r_string _name)
	{
		m_Name = _name;
	}

	r_string SteeringFormation::getName()
	{
		return m_Name;
	}
}