#include "stdafx.h"


namespace gmk
{
	void MapGenerator::placeRooms(PathfindingMap* _Map, const r_vector2i& _MapSize, const r_uint32& _MaxRoom, const r_vector2i& _MinRoomSize, const r_vector2i& _MaxRoomSize)
	{
		vector<Room*> RoomArray;

		for( r_uint32 i(0); i < _MaxRoom; i++ )
		{
			r_vector2i RoomSize(RAND(_MinRoomSize.x, _MaxRoomSize.x), RAND(_MinRoomSize.y, _MaxRoomSize.y));
			r_vector2i RoomPosition(RAND(1, (_MapSize.x - RoomSize.x - 1)), RAND(1, (_MapSize.y - RoomSize.y - 1)));

			Room* NewRoom = new Room(RoomPosition, RoomSize);

			r_bool bFailed(false);
			for( r_uint32 j(0); j < RoomArray.getElementNumber() && !bFailed; j++ )
			{
				if( (bFailed = NewRoom->intersects(*RoomArray[j])) )
					delete NewRoom;
			}

			if( !bFailed )
			{
				r_vector2i NewCenter = NewRoom->getCenter();

				if( RoomArray.getElementNumber() > 0 )
				{
					r_vector2i PreviousCenter = RoomArray[RoomArray.getElementNumber() - 1]->getCenter();

					if( RAND(0, 1) == 0 )
					{
						/*hCorridor(Std.int(prevCenter.x), Std.int(newCenter.x),
								  Std.int(prevCenter.y));
						vCorridor(Std.int(prevCenter.y), Std.int(newCenter.y),
								  Std.int(newCenter.x));*/
					}
					else
					{
						/*vCorridor(Std.int(prevCenter.y), Std.int(newCenter.y),
								  Std.int(prevCenter.x));
						hCorridor(Std.int(prevCenter.x), Std.int(newCenter.x),
								  Std.int(newCenter.y));*/
					}
				}

				RoomArray.push_back(NewRoom);
			}
		}

		for( r_uint32 i(0); i < RoomArray.getElementNumber(); i++ )
		{
			Room* CurrentRoom = RoomArray[i];
			r_vector2i CurrentPosition = CurrentRoom->getPosition();

			for( r_int32 j(0); j < CurrentRoom->getSize().x; j++ )
			{
				for( r_int32 k(0); k < CurrentRoom->getSize().y; k++ )
					_Map->setTerrainType(CurrentPosition.x + j, CurrentPosition.y + k, ePATHFINDING_TERRAIN_TYPE::eGROUND);
			}
		}

		RoomArray.deleteAndClear();
	}
}


/*private function hCorridor(x1:Int, x2 : Int, y) {
	for( x in Std.int(Math.min(x1, x2))...Std.int(Math.max(x1, x2)) + 1 ) {
		// destory the tiles to "carve" out corridor
		map[x][y].parent.removeChild(map[x][y]);

		// place a new unblocked tile
		map[x][y] = new Tile(Tile.DARK_GROUND, false, false);

		// add tile as a new game object
		addChild(map[x][y]);

		// set the location of the tile appropriately
		map[x][y].setLoc(x, y);
	}
}

// create vertical corridor to connect rooms
private function vCorridor(y1:Int, y2 : Int, x) {
	for( y in Std.int(Math.min(y1, y2))...Std.int(Math.max(y1, y2)) + 1 ) {
		// destroy the tiles to "carve" out corridor
		map[x][y].parent.removeChild(map[x][y]);

		// place a new unblocked tile
		map[x][y] = new Tile(Tile.DARK_GROUND, false, false);

		// add tile as a new game object
		addChild(map[x][y]);

		// set the location of the tile appropriately
		map[x][y].setLoc(x, y);
	}
}*/