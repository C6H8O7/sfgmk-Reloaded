namespace gmk
{
	ObbCollider::ObbCollider(GameObject* _gameobject, sf::Vector2f _Size) : Collider(_gameobject), m_Size(_Size)
	{
		m_Type = eCOLLIDER_TYPE::eOBB;
	}

	ObbCollider::~ObbCollider()
	{

	}
}