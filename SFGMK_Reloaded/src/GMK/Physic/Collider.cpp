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
		sf::CircleShape CircleShape;
		sf::RectangleShape RectShape;

		const sf::Transform Transform = m_GameObject->getTransform();
		float fSphereRadius;
		unsigned int uiDrawNumber(0U);

		if (m_bActive)
		{
			switch (m_Type)
			{
			case eCOLLIDER_TYPE::eSphere:
				fSphereRadius = m_Size.x;
				CircleShape.setRadius(fSphereRadius);
				CircleShape.setOutlineThickness(1);

				if (m_bCollide)
				{
					CircleShape.setFillColor(sf::Color(255, 0, 100, 75));
					CircleShape.setOutlineColor(sf::Color(255, 0, 150, 150));
				}
				else
				{
					CircleShape.setFillColor(sf::Color(0, 220, 150, 75));
					CircleShape.setOutlineColor(sf::Color(0, 220, 200, 150));
				}

				_render->draw(CircleShape, Transform);
				break;

			case eCOLLIDER_TYPE::eOBB:
				RectShape.setSize(m_Size);
				RectShape.setOutlineThickness(0.0f);

				if (m_bCollide)
				{
					RectShape.setFillColor(sf::Color(255, 0, 100, 75));
					RectShape.setOutlineColor(sf::Color(255, 0, 150, 150));
				}
				else
				{
					RectShape.setFillColor(sf::Color(0, 220, 150, 75));
					RectShape.setOutlineColor(sf::Color(0, 220, 200, 150));
				}

				_render->draw(RectShape, Transform);
				break;

			default:
				break;
			}
		}
	}
}