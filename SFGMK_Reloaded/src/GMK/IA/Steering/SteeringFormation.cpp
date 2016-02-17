#include "stdafx.h"

namespace gmk
{
	SteeringFormation::pSTEERING_FORMATION_FUNC SteeringFormation::s_FormationFuncs[FORMATION_COUNT] =
	{
		&SteeringFormation::getPositionFormationCircle,
		&SteeringFormation::getPositionFormationV,
		&SteeringFormation::getPositionFormationLine
	};

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
		m_LastFrameMaxIndex = m_CurrentPositionIndex;
		m_CurrentPositionIndex = 0;

		if ((!m_Leader && m_LeaderName.size()) || (m_Leader && m_Leader->name != m_LeaderName))
			m_Leader = SFMLCanvas::project->getCurrentScene()->findGameObjectByName(m_LeaderName);
	}

	r_vector2f SteeringFormation::getPosition(GameObject* _unit)
	{
		r_vector2f unit_position = _unit->transform.getPosition();

		if (!m_Leader || !m_Leader->rigidbodyPtr)
			return unit_position;

		return (this->*s_FormationFuncs[m_FormationFunc])(_unit);
	}

	r_void SteeringFormation::setLeader(GameObject* _leader)
	{
		m_Leader = _leader;

		if (m_Leader)
			m_LeaderName = m_Leader->name;
	}

	GameObject* SteeringFormation::getLeader()
	{
		return m_Leader;
	}

	r_vector2f SteeringFormation::getPositionFormationCircle(GameObject* _unit)
	{
		r_float index = (r_float)m_CurrentPositionIndex++;

		r_float angle = 2.0f * PI / (m_LastFrameMaxIndex + 0.001f);

		r_vector2f position = m_Leader->transform.getPosition();

		position.x += 200.0f * cosf(angle * index);
		position.y += 200.0f * sinf(angle * index);

		return position;
	}

	r_vector2f SteeringFormation::getPositionFormationV(GameObject* _unit)
	{
		r_float index = (r_float)m_CurrentPositionIndex++;

		r_float angle = 2.0f * PI / (m_LastFrameMaxIndex + 0.001f);

		r_vector2f position = m_Leader->transform.getPosition();

		position.x += 200.0f * cosf(angle * index);
		position.y += 200.0f * sinf(angle * index);

		return position;
	}

	r_vector2f SteeringFormation::getPositionFormationLine(GameObject* _unit)
	{
		r_int32 paramX = 2; // Nombre de membres par lignes
		r_float paramY = 10; // Distance inter membre

		r_int32 index = m_CurrentPositionIndex++;

		r_vector2f position = m_Leader->transform.getPosition();
		r_vector2f direction = m_Leader->rigidbodyPtr->getDirection();
		r_vector2f normal(-direction.y, direction.x);

		if (index % 2)
		{
			normal *= -1.0f;
			position = normal * ((r_float)(index % paramX)) - direction * 2.0f * ((index / paramX) + 1.0f);
		}
		else
		{
			position = normal * ((r_float)(index % paramX + 1)) - direction * 2.0f * ((index / paramX) + 1.0f);
		}

		position = position * paramY;
		position += m_Leader->transform.getPosition();

		return position;
	}
}