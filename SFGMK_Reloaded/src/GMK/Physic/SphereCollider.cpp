namespace gmk
{
	SphereCollider::SphereCollider(GameObject* _gameobject)
		: Collider(_gameobject)
	{
		m_Type = eCOLLIDER_TYPE::eSphere;
	}

	SphereCollider::~SphereCollider()
	{

	}

	r_float SphereCollider::getRadius()
	{
		return m_Size.x;
	}

	r_float SphereCollider::getSquaredRadius()
	{
		return m_Size.x * m_Size.x;
	}
}