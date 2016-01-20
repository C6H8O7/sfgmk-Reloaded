#include "stdafx.h"


namespace gmk
{
	Room::Room(const r_vector2i& _Position, const r_vector2i& _Size) : m_Position(_Position), m_Size(_Size)
	{
		m_Center = _Position + _Size / 2;
	}

	Room::~Room()
	{
	}


	bool Room::intersects(Room& _OtherRoom)
	{
		sf::IntRect ThisRoom(m_Position, m_Size);
		sf::IntRect OtherRoom(_OtherRoom.getPosition(), _OtherRoom.getSize());

		return ThisRoom.intersects(OtherRoom);
	}


	const r_vector2i& Room::getPosition()
	{
		return m_Position;
	}

	const r_vector2i& Room::getSize()
	{
		return m_Size;
	}

	const r_vector2i& Room::getCenter()
	{
		return m_Center;
	}
}