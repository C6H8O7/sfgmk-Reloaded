#include "stdafx.h"


namespace gmk
{
	void MapGenerator::generateClassic(PathfindingMap* _Map, const r_vector2i& _MapSize, const r_uint32& _MaxRoom, const r_vector2i& _MinRoomSize, const r_vector2i& _MaxRoomSize)
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
						horizontalCorridor(_Map, PreviousCenter.x, NewCenter.x, PreviousCenter.y);
						verticalCorridor(_Map, PreviousCenter.y, NewCenter.y, NewCenter.x);
					}
					else
					{
						verticalCorridor(_Map, PreviousCenter.y, NewCenter.y, PreviousCenter.x);
						horizontalCorridor(_Map, PreviousCenter.x, NewCenter.x, NewCenter.y);
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

	void MapGenerator::horizontalCorridor(PathfindingMap* _Map, const int& _PreviousCenterX, const int& _NewCenterX, const int& _Y)
	{
		r_int32 Max(MAX(_PreviousCenterX, _NewCenterX) + 1);

		for( r_int32 i(MIN(_PreviousCenterX, _NewCenterX)); i < Max; i++ )
			_Map->setTerrainType(i, _Y, ePATHFINDING_TERRAIN_TYPE::eGROUND);
	}

	void MapGenerator::verticalCorridor(PathfindingMap* _Map, const int& _PreviousCenterY, const int& _NewCenterY, const int& _X)
	{
		r_int32 Max(MAX(_PreviousCenterY, _NewCenterY) + 1);

		for( r_int32 i(MIN(_PreviousCenterY, _NewCenterY)); i < Max; i++ )
			_Map->setTerrainType(_X, i, ePATHFINDING_TERRAIN_TYPE::eGROUND);
	}
}