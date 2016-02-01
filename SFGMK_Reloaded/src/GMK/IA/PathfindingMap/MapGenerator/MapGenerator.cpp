#include "stdafx.h"


namespace gmk
{
	r_void MapGenerator::generateClassic(PathfindingMap* _Map, const r_vector2i& _MapSize, const r_uint32& _MaxRoom, const r_vector2i& _MinRoomSize, const r_vector2i& _MaxRoomSize)
	{
		vector<Room*> RoomArray;

		for( r_uint32 i(0); i < _MaxRoom; i++ )
		{
			r_vector2i RoomSize(RAND(_MinRoomSize.x, _MaxRoomSize.x), RAND(_MinRoomSize.y, _MaxRoomSize.y));
			r_vector2i RoomPosition(RAND(1, (_MapSize.x - RoomSize.x - 1)), RAND(1, (_MapSize.y - RoomSize.y - 1)));

			Room* NewRoom = new Room(RoomPosition, RoomSize);

			r_bool bFailed(false);
			for( r_uint32 j(0); j < RoomArray.size() && !bFailed; j++ )
			{
				if( (bFailed = NewRoom->intersects(*RoomArray[j])) )
					delete NewRoom;
			}

			if( !bFailed )
			{
				r_vector2i NewCenter = NewRoom->getCenter();

				if( RoomArray.size() > 0 )
				{
					r_vector2i PreviousCenter = RoomArray[RoomArray.size() - 1]->getCenter();

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

		for( r_uint32 i(0); i < RoomArray.size(); i++ )
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

	r_void MapGenerator::generateBsp(PathfindingMap* _Map, const r_vector2i& _MapSize, const r_uint32& _MaxRoom, const r_vector2i& _MinRoomSize, const r_vector2i& _MaxRoomSize)
	{
		vector<stBSP_NODE*> RoomArray;

		stBSP_NODE* Root = new stBSP_NODE(new Room(r_vector2i(0, 0), _MapSize), NULL, NULL);
		RoomArray.push_back(Root);

		for( r_uint32 i(0); i < RoomArray.size(); i++ )
		{
			stBSP_NODE* Temp = RoomArray[i];

			//Si ce noeud n'a pas encore été étendu
			if( !Temp->bClose )
			{
				std::cout << Temp->CurrentRoom->getPosition().x << '\t' << Temp->CurrentRoom->getPosition().y
					<< Temp->CurrentRoom->getSize().x << '\t' << Temp->CurrentRoom->getSize().y << std::endl;
				r_vector2i NewPositions[2] = { Temp->CurrentRoom->getPosition() };
				r_vector2i NewSizes[2];

				//Horizontal split
				if( RAND(0, 1) == 0 )
				{
					r_int32 uiSplit = RAND(1, Temp->CurrentRoom->getSize().x - 1);
					if( uiSplit > _MinRoomSize.x && (Temp->CurrentRoom->getSize().x - uiSplit) > _MinRoomSize.x )
					{
						NewPositions[1] = Temp->CurrentRoom->getPosition() + r_vector2i(uiSplit, 0);

						NewSizes[0] = Temp->CurrentRoom->getSize() - r_vector2i(Temp->CurrentRoom->getSize().x - uiSplit, 0);
						NewSizes[1] = Temp->CurrentRoom->getSize() - r_vector2i(uiSplit, 0);

						Temp->Childs[0] = new stBSP_NODE(new Room(NewPositions[0], NewSizes[0]), NULL, NULL);
						Temp->Childs[1] = new stBSP_NODE(new Room(NewPositions[1], NewSizes[1]), NULL, NULL);
						Temp->bClose = true;

						RoomArray.push_back(Temp->Childs[0]);
						RoomArray.push_back(Temp->Childs[1]);
					}
				}
				//Vertical split
				else
				{
					r_int32 uiSplit = RAND(1, Temp->CurrentRoom->getSize().y - 1);
					if( uiSplit > _MinRoomSize.y && (Temp->CurrentRoom->getSize().y - uiSplit) > _MinRoomSize.y )
					{
						NewPositions[1] = Temp->CurrentRoom->getPosition() + r_vector2i(0, uiSplit);

						NewSizes[0] = Temp->CurrentRoom->getSize() - r_vector2i(0, Temp->CurrentRoom->getSize().y - uiSplit);
						NewSizes[1] = Temp->CurrentRoom->getSize() - r_vector2i(0, uiSplit);

						Temp->Childs[0] = new stBSP_NODE(new Room(NewPositions[0], NewSizes[0]), NULL, NULL);
						Temp->Childs[1] = new stBSP_NODE(new Room(NewPositions[1], NewSizes[1]), NULL, NULL);
						Temp->bClose = true;

						RoomArray.push_back(Temp->Childs[0]);
						RoomArray.push_back(Temp->Childs[1]);
					}
				}
				/*
				Temp->Childs[0] = new stBSP_NODE(new Room(NewPositions[0], NewSizes[0]), NULL, NULL);
				Temp->Childs[1] = new stBSP_NODE(new Room(NewPositions[1], NewSizes[1]), NULL, NULL);
				Temp->bClose = true;

				RoomArray.push_back(Temp->Childs[0]);
				RoomArray.push_back(Temp->Childs[1]);*/
			}
		}
	}


	r_void MapGenerator::horizontalCorridor(PathfindingMap* _Map, const r_int32& _PreviousCenterX, const r_int32& _NewCenterX, const r_int32& _iY)
	{
		r_int32 Max(MAX(_PreviousCenterX, _NewCenterX) + 1);

		for( r_int32 i(MIN(_PreviousCenterX, _NewCenterX)); i < Max; i++ )
			_Map->setTerrainType(i, _iY, ePATHFINDING_TERRAIN_TYPE::eGROUND);
	}

	r_void MapGenerator::verticalCorridor(PathfindingMap* _Map, const r_int32& _PreviousCenterY, const r_int32& _NewCenterY, const r_int32& _iX)
	{
		r_int32 Max(MAX(_PreviousCenterY, _NewCenterY) + 1);

		for( r_int32 i(MIN(_PreviousCenterY, _NewCenterY)); i < Max; i++ )
			_Map->setTerrainType(_iX, i, ePATHFINDING_TERRAIN_TYPE::eGROUND);
	}
}