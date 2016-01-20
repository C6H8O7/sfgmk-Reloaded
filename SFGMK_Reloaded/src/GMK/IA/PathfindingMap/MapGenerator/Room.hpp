/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		19/01/2016
	@brief		

--------------------------------------------------------------------------------------------------*/

#ifndef ROOM_HPP
#define ROOM_HPP

#include "stdafx.h"


namespace gmk
{
	class Room
	{
		public:
			Room(const r_vector2i& _Position, const r_vector2i& _Size);
			~Room();

		private:
			r_vector2i m_Position;
			r_vector2i m_Size;
			r_vector2i m_Center;
	
		public:
			bool intersects(Room& _OtherRoom);

			const r_vector2i& getPosition();
			const r_vector2i& getSize();
			const r_vector2i& getCenter();
	};
}


#endif