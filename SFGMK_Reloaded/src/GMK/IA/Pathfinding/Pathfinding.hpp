/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		27/11/2015
	@brief		Classe premettant de calculer un chemin en utilisant différents algos

--------------------------------------------------------------------------------------------------*/

#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "stdafx.h"

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

			r_void precomputePaths(const ePATHFINDING_ALGOS& _Algo, PathfindingMap* _Map);
			r_void precomputeNeuronNetwork(r_int32 _nbIt, std::vector<r_uint32> _structure);
			r_vector2f getNeuronPrecomputedDirection(r_float _x1, r_float _y1, r_float _x2, r_float _y2);

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

			struct sPRECOMPUTED_PATH
			{
				r_float x1, y1;
				r_float x2, y2;
				r_float xs, ys;
			};

			std::vector<sPRECOMPUTED_PATH> m_PrecomputedPaths;
			NeuronNetwork network;

			r_void zPath();
			r_void dijkstra();
			r_void aStar();
	};
}


#endif