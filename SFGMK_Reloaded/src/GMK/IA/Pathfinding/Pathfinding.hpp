/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		27/11/2015
	@brief		Classe premettant de calculer un chemin en utilisant différents algos

--------------------------------------------------------------------------------------------------*/

#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP


namespace gmk
{
	typedef gmk::vector<r_vector2i> PathfindingPathCntr;

	enum ePATHFINDING_ALGOS
	{
		eZpath = 0,
		eDijkstra,
		eAStar,
		eJps,
		ePATHFINDING_ALGOS_NUMBER
	};

	class Pathfinding
	{
		public:
			Pathfinding();
			~Pathfinding();

			enum eEXPANDED_CASES
			{
				eTop = 0,
				eRight,
				eBot,
				eLeft,
				eEXPANDED_CASES_NUMBER_4 = 4,

				eTopRight = 4,
				eBotRight,
				eBotLeft,
				eTopLeft,
				eEXPANDED_CASES_NUMBER_8
			};

			enum eLIST_POSITION
			{
				eNone = 0,
				eOpenList,
				eCloseList
			};

			struct stEXPANDED_NODES
			{
				r_vector2i Coords;
				r_int32 iIndex;
			};

			struct stPATHFINDING_NODE
			{
				r_vector2i GridCoords;
				stPATHFINDING_NODE* ParentPtr;
				r_vector2i DirectionFromParent;

				r_float fCostSoFar;
				r_float fHeuristic;
				r_float fEstimatedTotalCost;

				stPATHFINDING_NODE(const r_vector2i& _GridCoord, stPATHFINDING_NODE* _Parent = NULL, const r_vector2i& DirectionFromParent = r_vector2i(0, 0), const r_float& _CostSoFar = 0.0f, const r_float& _Heuristic = 0.0f, const r_float& _EstimatedTotalCost = 0.0f)
					:  GridCoords(_GridCoord), ParentPtr(_Parent), DirectionFromParent(DirectionFromParent), fCostSoFar(_CostSoFar), fHeuristic(_Heuristic), fEstimatedTotalCost(_EstimatedTotalCost) {}
			};

			struct stPATHFINDING_GRID_NODE
			{
				r_bool bTested;
				r_uint32 uiStep;
				eLIST_POSITION List;
			};

		private:
			r_vector2i m_PrecomputedNextCases[eEXPANDED_CASES_NUMBER_8];
			stEXPANDED_NODES m_ExpandedNodes[eEXPANDED_CASES_NUMBER_8];

			FoncterTemplateArray m_Algorithms;
			r_string m_sAlgosNames[ePATHFINDING_ALGOS_NUMBER];

			PathfindingMap* m_Map;
			stPATHFINDING_GRID_NODE* m_NodeMap;
			r_vector2i m_Begin, m_End, m_Size;
			PathfindingPathCntr* m_Path;
			r_bool m_bGoalFound;
			r_uint32 m_uiStep;
			sf::Clock m_Clock;
			sf::Int64 m_ElapsedTime;

			//Z-Path
			std::queue<r_vector2i> m_ZPathList;

			//A*
			std::list<stPATHFINDING_NODE*> m_OpenList;
			std::list<stPATHFINDING_NODE*> m_CloseList;

		public:
			r_void computePathfinding(PathfindingPathCntr* _Path, const ePATHFINDING_ALGOS& _Algo, PathfindingMap* _Map, const r_vector2i& _Begin, const r_vector2i& _End, const r_bool& _SmoothPath = false, const r_float& _CaseSize = 0.0f);
			r_void smoothPath(PathfindingPathCntr* _Path, const r_float& _CaseSize);

			stPATHFINDING_GRID_NODE* getGridNodeMap() { return m_NodeMap; }

		private:
			inline r_void allocNodeMap()
			{
				m_NodeMap = (stPATHFINDING_GRID_NODE*)calloc(m_Map->getCaseNumber(), sizeof(stPATHFINDING_GRID_NODE));
			}
			inline r_void resetNodeMap()
			{
				memset(m_NodeMap, 0, sizeof(stPATHFINDING_GRID_NODE) * m_Map->getCaseNumber());
			}
			inline r_void releaseNodeMap()
			{
				if( m_NodeMap != NULL )
				{
					free(m_NodeMap);
					m_NodeMap = NULL;
				}
			}

			inline r_int32 computeExpandedCases4(const r_vector2i& _CurrentCase)
			{
				r_int32 iArrayIndex(0);

				for( r_int32 i(0); i < eEXPANDED_CASES_NUMBER_4; i++ )
				{
					m_ExpandedNodes[iArrayIndex].Coords = _CurrentCase + m_PrecomputedNextCases[i];

					//Si la case est dans la map
					if( (m_ExpandedNodes[iArrayIndex].iIndex = m_Map->getSafeIndex(m_ExpandedNodes[iArrayIndex].Coords)) != eOUT_OF_MAP )
					{
						//Si la case n'est pas un mur
						if( !(m_Map->isWall(m_ExpandedNodes[iArrayIndex].iIndex)) )
							iArrayIndex++;
					}
				}

				return iArrayIndex;
			}
			inline r_int32 computeExpandedCases8(const r_vector2i& _CurrentCase)
			{
				r_int32 iArrayIndex(0);

				for( r_int32 i(0); i < eEXPANDED_CASES_NUMBER_8; i++ )
				{
					m_ExpandedNodes[iArrayIndex].Coords = _CurrentCase + m_PrecomputedNextCases[i];

					//Si la case est dans la map
					if( (m_ExpandedNodes[iArrayIndex].iIndex = m_Map->getSafeIndex(m_ExpandedNodes[iArrayIndex].Coords)) != eOUT_OF_MAP )
					{
						//Si la case n'est pas un mur
						if( !(m_Map->isWall(m_ExpandedNodes[iArrayIndex].iIndex)) )
						{
							//Si on ne traverse pas un mur en diagonale
							if( i < eEXPANDED_CASES_NUMBER_4 || !m_Map->checkDiagonalWall(_CurrentCase, m_ExpandedNodes[iArrayIndex].Coords) )
								iArrayIndex++;
						}
					}
				}

				return iArrayIndex;
			}

			inline stPATHFINDING_NODE* findSmallestNode(std::list<stPATHFINDING_NODE*>& _list)
			{
				r_float value = -1.0f;
				stPATHFINDING_NODE* node = 0;

				for( stPATHFINDING_NODE*& _node : _list )
				{
					if( _node->fEstimatedTotalCost < value || value < 0.0f )
					{
						node = _node;
						value = _node->fEstimatedTotalCost;
					}
				}
				return node;
			}
			inline stPATHFINDING_NODE* searchInList(const r_vector2i& _node, std::list<stPATHFINDING_NODE*>& _list)
			{
				for( stPATHFINDING_NODE*& Temp : _list )
					if( _node == Temp->GridCoords )
						return Temp;

				return NULL;
			}

			inline r_void forcedNeighbours(r_vector2i& _current, r_vector2i& _dir, r_vector2i _forced[8], r_int32* _forcedCount)
			{
				r_vector2i testWall;

				// Diagonal
				if( _dir.x && _dir.y )
				{
					testWall = r_vector2i(_current.x - _dir.x, _current.y);
					if( m_Map->getSafeIndex(testWall) != eOUT_OF_MAP && m_Map->isWall(m_Map->getSafeIndex(testWall)) )
					{
						r_vector2i forced(_current.x - _dir.x, _current.y + _dir.y);

						if( m_Map->getSafeIndex(forced) != eOUT_OF_MAP && !m_Map->isWall(m_Map->getSafeIndex(forced)) )
							_forced[(*_forcedCount)++] = forced;
					}
					testWall = r_vector2i(_current.x, _current.y - _dir.y);
					if( m_Map->getSafeIndex(testWall) != eOUT_OF_MAP && m_Map->isWall(m_Map->getSafeIndex(testWall)) )
					{
						r_vector2i forced(_current.x + _dir.x, _current.y - _dir.y);

						if( m_Map->getSafeIndex(forced) != eOUT_OF_MAP && !m_Map->isWall(m_Map->getSafeIndex(forced)) )
							_forced[(*_forcedCount)++] = forced;
					}
				}
				// Horizontal
				else if( _dir.x )
				{
					testWall = r_vector2i(_current.x, _current.y - 1);
					if( m_Map->getSafeIndex(testWall) != eOUT_OF_MAP && m_Map->isWall(m_Map->getSafeIndex(testWall)) )
					{
						r_vector2i forced(_current.x + _dir.x, _current.y - 1);

						if( m_Map->getSafeIndex(forced) != eOUT_OF_MAP && !m_Map->isWall(m_Map->getSafeIndex(forced)) )
							_forced[(*_forcedCount)++] = forced;
					}
					testWall = r_vector2i(_current.x, _current.y + 1);
					if( m_Map->getSafeIndex(testWall) != eOUT_OF_MAP && m_Map->isWall(m_Map->getSafeIndex(testWall)) )
					{
						r_vector2i forced(_current.x + _dir.x, _current.y + 1);

						if( m_Map->getSafeIndex(forced) != eOUT_OF_MAP && !m_Map->isWall(m_Map->getSafeIndex(forced)) )
							_forced[(*_forcedCount)++] = forced;
					}
				}
				// Vertical
				else if( _dir.y )
				{
					testWall = r_vector2i(_current.x - 1, _current.y);
					if( m_Map->getSafeIndex(testWall) != eOUT_OF_MAP && m_Map->isWall(m_Map->getSafeIndex(testWall)) )
					{
						r_vector2i forced(_current.x - 1, _current.y + _dir.y);

						if( m_Map->getSafeIndex(forced) != eOUT_OF_MAP && !m_Map->isWall(m_Map->getSafeIndex(forced)) )
							_forced[(*_forcedCount)++] = forced;
					}
					testWall = r_vector2i(_current.x + 1, _current.y);
					if( m_Map->getSafeIndex(testWall) != eOUT_OF_MAP && m_Map->isWall(m_Map->getSafeIndex(testWall)) )
					{
						r_vector2i forced(_current.x + 1, _current.y + _dir.y);

						if( m_Map->getSafeIndex(forced) != eOUT_OF_MAP && !m_Map->isWall(m_Map->getSafeIndex(forced)) )
							_forced[(*_forcedCount)++] = forced;
					}
				}
			}
			inline r_void neighbours(r_vector2i& _current, r_vector2i& _dir, r_vector2i _neighbours[8], r_int32* _neighboursCount)
			{
				if( _dir.x && _dir.y )
				{
					r_vector2i n[3];
					n[0] = r_vector2i(_current.x, _current.y + _dir.y);
					n[1] = r_vector2i(_current.x + _dir.x, _current.y);
					n[2] = r_vector2i(_current.x + _dir.x, _current.y + _dir.y);

					for( r_int32 i = 0; i < 3; i++ )
						if( m_Map->getSafeIndex(n[i]) != eOUT_OF_MAP && !m_Map->isWall(m_Map->getSafeIndex(n[i])) )
							_neighbours[(*_neighboursCount)++] = n[i];
				}
				else
				{
					r_vector2i n(_current.x + _dir.x, _current.y + _dir.y);

					if( m_Map->getSafeIndex(n) != eOUT_OF_MAP && !m_Map->isWall(m_Map->getSafeIndex(n)) )
						_neighbours[(*_neighboursCount)++] = n;
				}
			}
			inline r_void allNeighbours(r_vector2i& _current, r_vector2i& _dir, r_vector2i _allNeighbours[8], r_int32* _allNeighboursCount)
			{
				r_int32 countNormal = 0, countForced = 0;
				r_vector2i normal[8], forced[8];

				neighbours(_current, _dir, normal, &countNormal);
				forcedNeighbours(_current, _dir, forced, &countForced);

				for( r_int32 i = 0; i < countNormal; i++ )
					_allNeighbours[(*_allNeighboursCount)++] = normal[i];

				for( r_int32 i = 0; i < countForced; i++ )
					_allNeighbours[(*_allNeighboursCount)++] = forced[i];
			}
			inline r_vector2i* jump(r_vector2i& _current, r_vector2i& _start, r_vector2i& _end, r_vector2i& _dir)
			{
				stEXPANDED_NODES next = { _current + _dir, m_Map->getSafeIndex(_current + _dir) };
		
				if( next.iIndex == eOUT_OF_MAP || m_Map->isWall(next.iIndex) )
					return 0;

				// On vérifie qu'on est pas tombés sur l'arrivée
				if( next.Coords == _end )
					return new r_vector2i(_end);

				// Vérification voisin forcé
				r_int32 forced_count = 0;
				r_vector2i forced[8];
				forcedNeighbours(_current, _dir, forced, &forced_count);

				// Si il y a un voisin forcé, on ajoute le point de saut
				if( forced_count )
					return new r_vector2i(next.Coords);

				// Cas en diagonal
				if( _dir.x && _dir.y )
				{
					if( jump(next.Coords, _start, _end, r_vector2i(_dir.x, 0))
					   || jump(next.Coords, _start, _end, r_vector2i(0, _dir.y)) )
					{
						return new r_vector2i(next.Coords);
					}
				}

				return jump(next.Coords, _start, _end, _dir);
			}
			inline r_void identifySuccessors(r_vector2i& _current, r_vector2i& _start, r_vector2i& _end, r_int32* _validSuccessors)
			{
				r_int32 iValid_expanded_nodes = 0;

				// On récupère tous les voisins valables
				r_float dx = (r_float)(_end.x - _start.x);
				r_float dy = (r_float)(_end.y - _start.y);

				r_vector2i dir((r_int32)(dx / ABS(dx)), (r_int32)(dy / ABS(dy)));
				//jps_all_neighbours(_current, dir, expanded_nodes, &valid_expanded_nodes);
				iValid_expanded_nodes = computeExpandedCases8(_current);

				r_vector2i direction;

				for( r_int32 i = 0; i < iValid_expanded_nodes; i++ )
				{
					r_vector2i& expanded_node = m_ExpandedNodes[i].Coords;

					direction = expanded_node - _current;

					// On tente de trouver un nouveau point de saut
					r_vector2i* jumpPoint = jump(_current, _start, _end, direction);

					if( jumpPoint )
					{
						m_ExpandedNodes[(*_validSuccessors)].iIndex = m_Map->getIndex(*jumpPoint);
						m_ExpandedNodes[(*_validSuccessors)++].Coords = *jumpPoint;
					}
				}
			}

			r_void zPath();
			r_void dijkstra();
			r_void aStar();
			r_void jps();
	};
}


#endif