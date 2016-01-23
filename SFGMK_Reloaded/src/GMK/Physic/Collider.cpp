#include "stdafx.h"

namespace gmk
{
	Collider::Collider(GameObject* _gameobject)
		: m_bActive(true), m_bCollide(false), m_GameObject(_gameobject)
	{
		gmk::PhysicManager::getSingleton()->addCollider(this);
	}

	Collider::~Collider()
	{
		gmk::PhysicManager::getSingleton()->removeCollider(this);
	}

	const eCOLLIDER_TYPE& Collider::getType()
	{
		return m_Type;
	}

	r_void Collider::setType(eCOLLIDER_TYPE _type)
	{
		m_Type = _type;
	}

	const r_bool& Collider::isActive()
	{
		return m_bActive;
	}

	r_void Collider::setActive(r_bool _Boolean)
	{
		m_bActive = _Boolean;
	}

	const r_bool& Collider::isColliding()
	{
		return m_bCollide;
	}

	r_void Collider::setColliding(r_bool _Boolean)
	{
		m_bCollide = _Boolean;
	}

	const r_vector2f& Collider::getSize()
	{
		return m_Size;
	}

	r_void Collider::setSize(r_vector2f _size)
	{
		m_Size = _size;
	}

	const r_vector2f Collider::getWorldSize()
	{
		r_vector2f result = m_Size;

		result.x *= m_GameObject->transform.scale.x;
		result.y *= m_GameObject->transform.scale.y;

		return result;
	}

	const r_vector2f Collider::getOffset()
	{
		return m_Offset;
	}

	r_void Collider::setOffset(r_vector2f _offset)
	{
		m_Offset = _offset;
	}

	GameObject* Collider::getGameObject()
	{
		return m_GameObject;
	}

	r_void Collider::setGameObject(GameObject* _object)
	{
		m_GameObject = _object;
	}

	r_void Collider::draw(sf::RenderTarget* _render)
	{
		static sf::CircleShape CircleShape;
		static sf::RectangleShape RectShape;

		sf::Transform Transform = m_GameObject->getTransform();
		Transform.translate(m_Offset);

		if (m_bActive)
		{
			switch (m_Type)
			{
				case eCOLLIDER_TYPE::eSphere:
					CircleShape.setRadius(m_Size.x);
					CircleShape.setOutlineThickness(0.0f);

					if (m_bCollide)
						CircleShape.setFillColor(sf::Color(255, 0, 100, 75));
					else
						CircleShape.setFillColor(sf::Color(0, 220, 150, 75));

					_render->draw(CircleShape, Transform);
					break;

				case eCOLLIDER_TYPE::eOBB:
					RectShape.setSize(m_Size);
					RectShape.setOutlineThickness(0.0f);

					if (m_bCollide)
						RectShape.setFillColor(sf::Color(255, 0, 100, 75));
					else
						RectShape.setFillColor(sf::Color(0, 220, 150, 75));

					_render->draw(RectShape, Transform);
					break;
			}
		}
	}

	r_void Collider::addCollidingWith(Collider* _collider)
	{
		m_CollidingWith.push_back(_collider);
	}

	r_bool Collider::isCollidingWith(Collider* _collider)
	{
		for (r_uint32 i = 0; i < m_CollidingWith.size(); i++)
			if (m_CollidingWith[i] == _collider)
				return true;

		return false;
	}

	r_bool Collider::wasCollidingWith(Collider* _collider)
	{
		for (r_uint32 i = 0; i < m_PrevCollidingWith.size(); i++)
			if (m_PrevCollidingWith[i] == _collider)
				return true;

		return false;
	}

	r_bool Collider::beginCollidingWith(Collider* _collider)
	{
		return !wasCollidingWith(_collider) && isCollidingWith(_collider);
	}

	r_void Collider::updateCollidingWith()
	{
		m_PrevCollidingWith = m_CollidingWith;
		m_CollidingWith.clear();
	}
}