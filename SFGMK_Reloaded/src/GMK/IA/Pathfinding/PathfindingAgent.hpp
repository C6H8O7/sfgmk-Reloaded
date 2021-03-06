#ifndef SFGMKR_PATHFINDINGAGENT_HPP
#define SFGMKR_PATHFINDINGAGENT_HPP

#include "stdafx.h"

namespace gmk
{
	class PathfindingAgent
	{
	public:

		PathfindingAgent();
		~PathfindingAgent();

		r_void computePathfinding(r_vector2f _begin, r_vector2f _end, r_bool _smooth = false, r_float _caseSize = 0.0f);

		r_void setMap(PathfindingMap* _map);

		r_void setAlgo(ePATHFINDING_ALGOS _algo);

		r_vector2f getDirection(r_vector2f _position);

		r_void drawPath(sf::RenderTarget* _render, sf::Transform _transform = sf::Transform());

	private:

		Pathfinding m_Pathfinding;

		PathfindingMap* m_Map;
		
		ePATHFINDING_ALGOS m_Algo;

		PathfindingPathCntr m_Path;
	};
}

#endif