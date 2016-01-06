/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		12/12/2015
	@brief		Map sous forme de grille pour pathfinding

--------------------------------------------------------------------------------------------------*/

#ifndef PATHFINDING_MAP_HPP
#define PATHFINDING_MAP_HPP

#define BEGIN_COLOR sf::Color::Green
#define END_COLOR sf::Color::Red
#define CASE_OUTLINE_COLOR sf::Color::Blue
#define WALL_COLOR sf::Color(150, 150, 150, 192)
#define PATH_COLOR sf::Color(200, 255, 0, 150)
#define EXPLORATION_COLOR sf::Color(100, 255, 0, 100)

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

			r_uint8* m_uiMap;
			r_vector2i m_Size;
			r_uint32 m_uiCaseNumber;
			r_uint32 m_uiWallNumber;

			r_void freeMap();

			r_int32 m_CaseSize;
			r_vector2f m_Position;

		public:

			inline r_int32 getCaseSize()
			{
				return m_CaseSize;
			}
			inline r_void setCaseSize(r_int32 _caseSize)
			{
				m_CaseSize = _caseSize;
			}

			inline r_vector2f getPosition()
			{
				return m_Position;
			}
			inline r_void setPosition(r_vector2f _position)
			{
				m_Position = _position;
			}

			inline r_int32 getIndex(const r_vector2i& _Position)
			{
				return _Position.y * m_Size.x + _Position.x;
			}

			inline r_int32 getSafeIndex(const r_vector2i& _Position)
			{
				if( !isInMap(_Position) )
					return eOUT_OF_MAP;

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

			r_uint8* getMap();
			const r_vector2i& getSize();
			const r_uint32& getCaseNumber();
			const r_uint32& getWallNumber();

			r_bool loadMapFromFile(const r_int8* _FileName, r_vector2i& _Begin, r_vector2i& _End);

			r_void resize(const r_int32& _X, const r_int32& _Y);

			r_void calcWallNumber();

			r_void setTerrainType(const r_int32& _X, const r_int32& _Y, const ePATHFINDING_TERRAIN_TYPE& _Type);

			r_void draw(sf::RenderTarget* _render, sf::Transform _transform = sf::Transform());

			r_vector2i getMouseCase(const sf::Vector2f& _MouseWorldPos)
			{
				return sf::Vector2i((int)((_MouseWorldPos.x - m_Position.x) / m_CaseSize), (int)((_MouseWorldPos.y - m_Position.y) / m_CaseSize));
			}
	};
}


#endif