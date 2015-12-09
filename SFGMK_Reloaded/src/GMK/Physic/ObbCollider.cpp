namespace gmk
{
	ObbCollider::ObbCollider(GameObject* _gameobject) : Collider(_gameobject)
	{
		m_Type = eCOLLIDER_TYPE::eOBB;
	}

	ObbCollider::~ObbCollider()
	{

	}
}