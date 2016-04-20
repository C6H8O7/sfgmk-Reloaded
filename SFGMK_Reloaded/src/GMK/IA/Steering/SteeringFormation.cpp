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

		m_ParsedParams.clear();
		std::vector<r_string> params = gmk::stringSplit(m_Params, ' ');
		for (r_uint32 i = 0; i < params.size(); i++)
			m_ParsedParams.push_back((r_float)atof(params[i].c_str()));

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
		if (m_ParsedParams.size() < 3)
			return _unit->transform.getPosition();

		r_int32 membersPerCircle = (r_int32)m_ParsedParams[0];
		r_float distanceBetweenCircles = m_ParsedParams[1];
		r_float initialDistance = m_ParsedParams[2];

		r_int32 index = m_CurrentPositionIndex++;

		r_int32 circle = index / membersPerCircle;
		r_int32 indexOnCircle = index % membersPerCircle;

		r_float angle = 2.0f * PI / membersPerCircle * indexOnCircle;
		r_float radius = initialDistance + distanceBetweenCircles * circle;

		r_vector2f position = m_Leader->transform.getPosition();

		position.x += radius * cosf(angle);
		position.y += radius * sinf(angle);

		return position;
	}

	r_vector2f SteeringFormation::getPositionFormationV(GameObject* _unit)
	{
		if (m_ParsedParams.size() < 2)
			return _unit->transform.getPosition();

		r_int32 membersPerLine = (r_int32)m_ParsedParams[0];
		r_float distance = m_ParsedParams[1];

		r_int32 index = m_CurrentPositionIndex++;

		r_vector2f position = m_Leader->transform.getPosition();
		r_vector2f direction = m_Leader->rigidbodyPtr->getDirection();
		r_vector2f normal(-direction.y, direction.x);

		if (index & 1)
		{
			normal *= -1.0f;
			position = normal * (r_float)(index % membersPerLine) - direction * 2.0f * (r_float)((index / membersPerLine) + index%membersPerLine);
		}
		else
		{
			position = normal * (r_float)(index % membersPerLine + 1) - direction * 2.0f * (r_float)((index / membersPerLine) + index%membersPerLine + 1);
		}

		position *= distance;
		position += m_Leader->transform.getPosition();

		return position;
	}

	r_vector2f SteeringFormation::getPositionFormationLine(GameObject* _unit)
	{
		if (m_ParsedParams.size() < 2)
			return _unit->transform.getPosition();

		r_int32 paramX = (r_int32)m_ParsedParams[0];	// Nombre de membres par lignes
		r_float paramY = m_ParsedParams[1];				// Distance inter membre

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