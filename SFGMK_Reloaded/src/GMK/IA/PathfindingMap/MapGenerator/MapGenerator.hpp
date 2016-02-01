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
		struct stBSP_NODE
		{
			Room* CurrentRoom;
			stBSP_NODE* Childs[2];
			bool bClose;

			stBSP_NODE(Room* _Current, stBSP_NODE* _ChildOne, stBSP_NODE* _ChildTwo) : CurrentRoom(_Current), bClose(false) { Childs[0] = _ChildOne; Childs[1] = _ChildTwo; }
		};

		public:
			static r_void generateClassic(PathfindingMap* _Map, const r_vector2i& _MapSize, const r_uint32& _MaxRoom, const r_vector2i& _MinRoomSize, const r_vector2i& _MaxRoomSize);
			static r_void generateBsp(PathfindingMap* _Map, const r_vector2i& _MapSize, const r_uint32& _MaxRoom, const r_vector2i& _MinRoomSize, const r_vector2i& _MaxRoomSize);

		private:
			static r_void horizontalCorridor(PathfindingMap* _Map, const r_int32& _PreviousCenterX, const r_int32& _NewCenterX, const r_int32& _Y);
			static r_void verticalCorridor(PathfindingMap* _Map, const r_int32& _PreviousCenterY, const r_int32& _NewCenterY, const r_int32& _X);
	};
}


#endif
