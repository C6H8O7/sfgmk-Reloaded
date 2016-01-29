/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		19/01/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

#include "stdafx.h"


namespace gmk
{
	class MapGenerator
	{
		public:
			static void generateClassic(PathfindingMap* _Map, const r_vector2i& _MapSize, const r_uint32& _MaxRoom, const r_vector2i& _MinRoomSize, const r_vector2i& _MaxRoomSize);

		private:
			static void horizontalCorridor(PathfindingMap* _Map, const int& _PreviousCenterX, const int& _NewCenterX, const int& _iY);
			static void verticalCorridor(PathfindingMap* _Map, const int& _PreviousCenterY, const int& _NewCenterY, const int& _iX);
	};
}


#endif
