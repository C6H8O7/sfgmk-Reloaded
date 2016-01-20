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
			static void placeRooms(PathfindingMap* _Map, const r_vector2i& _MapSize, const r_uint32& _MaxRoom, const r_vector2i& _MinRoomSize, const r_vector2i& _MaxRoomSize);
	};
}


#endif
