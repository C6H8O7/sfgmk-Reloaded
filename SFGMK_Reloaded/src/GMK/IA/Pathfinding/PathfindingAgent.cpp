#include "stdafx.h"

namespace gmk
{
	PathfindingAgent::PathfindingAgent()
		: m_Map(0), m_Algo(ePATHFINDING_ALGOS::eZpath)
	{

	}

	PathfindingAgent::~PathfindingAgent()
	{

	}

	r_void PathfindingAgent::computePathfinding(r_vector2f _begin, r_vector2f _end, r_bool _smooth, r_float _caseSize)
	{
		if (!m_Map)
			return;

		r_int32 caseSize = m_Map->getCaseSize();

		_begin -= m_Map->getPosition();
		_end -= m_Map->getPosition();

		r_vector2i begin, end;

		begin.x = (r_int32)(_begin.x / caseSize);
		begin.y = (r_int32)(_begin.y / caseSize);

		end.x = (r_int32)(_end.x / caseSize);
		end.y = (r_int32)(_end.y / caseSize);

		int is = m_Map->getSafeIndex(begin);
		int ie = m_Map->getSafeIndex(end);

		if (is >= 0 && ie >= 0 && !m_Map->isWall(is) && !m_Map->isWall(ie))
			m_Pathfinding.computePathfinding(&m_Path, m_Algo, m_Map, begin, end, true, caseSize);
	}

	r_void PathfindingAgent::setMap(PathfindingMap * _map)
	{
		m_Map = _map;
	}

	r_void PathfindingAgent::setAlgo(ePATHFINDING_ALGOS _algo)
	{
		m_Algo = _algo;
	}

	r_vector2f PathfindingAgent::getDirection(r_vector2f _position)
	{
		if (!m_Map || !m_Path.size())
			return r_vector2f();

		r_vector2f next = ((r_vector2f)m_Path[0]) * (float)m_Map->getCaseSize() + m_Map->getPosition();
		r_vector2f diff = next - _position;
		
		if (diff.x * diff.x < 1.0f && diff.y * diff.y < 1.0f)
		{
			m_Path.pop_front();
			return getDirection(_position);
		}

		return math::Calc_UnitVector(diff);
	}

	r_void PathfindingAgent::drawPath(sf::RenderTarget* _render, sf::Transform _transform)
	{
		if (!m_Map)
			return;

		r_int32 caseSize = m_Map->getCaseSize();

		//Draw path
		sf::CircleShape Circle(caseSize * 0.5f, 8);
		Circle.setFillColor(PATH_COLOR);
		Circle.setOutlineThickness(0);

		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(10, 10), sf::Color::Green),
			sf::Vertex(sf::Vector2f(150, 150), sf::Color::Green)
		};

		for (size_t i(0); i < m_Path.size(); i++)
		{
			Circle.setPosition(sf::Vector2f((r_float)m_Path[i].x * caseSize, (r_float)m_Path[i].y * caseSize));
			_render->draw(Circle, _transform);

			if (i < m_Path.size() - 1)
			{
				line[0].position = sf::Vector2f(m_Path[i].x * caseSize + caseSize * 0.5f, m_Path[i].y * caseSize + caseSize * 0.5f);
				line[1].position = sf::Vector2f(m_Path[i + 1].x * caseSize + caseSize * 0.5f, m_Path[i + 1].y * caseSize + caseSize * 0.5f);
				_render->draw(line, 2, sf::Lines, _transform);
			}
		}
	}
}