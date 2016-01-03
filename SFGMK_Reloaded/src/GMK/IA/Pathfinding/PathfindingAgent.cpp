namespace gmk
{
	PathfindingAgent::PathfindingAgent()
		: m_Map(0)
	{

	}

	PathfindingAgent::~PathfindingAgent()
	{

	}

	r_void PathfindingAgent::computePathfinding(r_vector2f _begin, r_vector2f _end, r_bool _smooth, r_float _caseSize)
	{
		if (!m_Map)
			return;

		r_vector2i begin, end;

		begin.x = (r_int32)(_begin.x / ARRAY_CASE_SIZE);
		begin.y = (r_int32)(_begin.y / ARRAY_CASE_SIZE);

		end.x = (r_int32)(_end.x / ARRAY_CASE_SIZE);
		end.y = (r_int32)(_end.y / ARRAY_CASE_SIZE);

		int is = m_Map->getSafeIndex(begin);
		int ie = m_Map->getSafeIndex(end);

		if (is >= 0 && ie >= 0 && !m_Map->isWall(is) && !m_Map->isWall(ie))
			m_Pathfinding.computePathfinding(&m_Path, gmk::ePATHFINDING_ALGOS::eZpath, m_Map, begin, end, true, ARRAY_CASE_SIZE);
	}

	r_void PathfindingAgent::setMap(PathfindingMap * _map)
	{
		m_Map = _map;
	}

	r_vector2f PathfindingAgent::getDirection()
	{
		return r_vector2f();
	}

	r_void PathfindingAgent::drawPath(sf::RenderTarget* _render)
	{
		//Draw path
		sf::CircleShape Circle(ARRAY_CASE_SIZE * 0.5f, 8);
		Circle.setFillColor(PATH_COLOR);
		Circle.setOutlineThickness(0);

		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(10, 10), sf::Color::Green),
			sf::Vertex(sf::Vector2f(150, 150), sf::Color::Green)
		};

		for (size_t i(0); i < m_Path.size(); i++)
		{
			Circle.setPosition(sf::Vector2f(m_Path[i].x * ARRAY_CASE_SIZE, m_Path[i].y * ARRAY_CASE_SIZE));
			_render->draw(Circle);

			if (i < m_Path.size() - 1)
			{
				line[0].position = sf::Vector2f(m_Path[i].x * ARRAY_CASE_SIZE + ARRAY_CASE_SIZE * 0.5f, m_Path[i].y * ARRAY_CASE_SIZE + ARRAY_CASE_SIZE * 0.5f);
				line[1].position = sf::Vector2f(m_Path[i + 1].x * ARRAY_CASE_SIZE + ARRAY_CASE_SIZE * 0.5f, m_Path[i + 1].y * ARRAY_CASE_SIZE + ARRAY_CASE_SIZE * 0.5f);
				_render->draw(line, 2, sf::Lines);
			}
		}
	}
}