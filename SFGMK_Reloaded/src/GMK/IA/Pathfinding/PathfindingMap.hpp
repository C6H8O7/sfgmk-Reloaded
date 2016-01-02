/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		12/12/2015
	@brief		Map sous forme de grille pour pathfinding

--------------------------------------------------------------------------------------------------*/

#ifndef PATHFINDING_MAP_HPP
#define PATHFINDING_MAP_HPP


namespace gmk
{
	enum ePATHFINDING_TERRAIN_TYPE
	{
		eOUT_OF_MAP = -1,
		eWALL = 0,
		eGROUND = 1
	};

	class PathfindingMap
	{
		public:
			PathfindingMap();
			~PathfindingMap();

		private:
			sf::Uint8* m_uiMap;
			r_vector2i m_Size;
			r_uint32 m_uiCaseNumber;

			r_void freeMap();

		public:
			inline r_int32 getIndex(const r_vector2i& _Position)
			{
				return _Position.y * m_Size.x + _Position.x;
			}
			inline r_int32 getSafeIndex(const r_vector2i& _Position)
			{
				if( !isInMap(_Position) ) return eOUT_OF_MAP;
				return _Position.y * m_Size.x + _Position.x;
			}
			inline r_bool isInMap(const r_vector2i& _Position)
			{
				if( _Position.x < 0 || _Position.x >= m_Size.x ) return false;
				if( _Position.y < 0 || _Position.y >= m_Size.y ) return false;
				return true;
			}
			inline r_int32 getTerrainType(const r_vector2i& _Position)
			{
				r_int32 iIndex = getIndex(_Position);
				if( iIndex == eOUT_OF_MAP )
					return iIndex;
				return m_uiMap[iIndex];
			}
			inline r_bool isWall(const r_int32& _Index)
			{
				return (m_uiMap[_Index] == eWALL);
			}
			inline r_bool checkDiagonalWall(const r_vector2i& _CaseOne, const r_vector2i& _CaseTwo)
			{
				r_vector2i m_CasesToTest[2] = { r_vector2i(_CaseOne.x, _CaseTwo.y), r_vector2i(_CaseTwo.x, _CaseOne.y) };
			
				if( isWall(getIndex(m_CasesToTest[0])) && isWall(getIndex(m_CasesToTest[1])) )
					return true;
				else
					return false;
			}

			sf::Uint8* getMap();
			const r_vector2i& getSize();
			const r_uint32& getCaseNumber();

			r_bool loadMapFromFile(const r_int8* _FileName, r_vector2i& _Begin, r_vector2i& _End);

			r_void setTerrainType(const r_int32& _X, const r_int32& _Y, const ePATHFINDING_TERRAIN_TYPE& _Type);
	};
}


#endif