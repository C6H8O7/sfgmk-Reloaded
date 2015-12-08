namespace gmk
{
	Collider::Collider(GameObject* _gameobject) : m_bActive(true), m_bCollide(false), m_GameObject(_gameobject)
	{

	}

	Collider::~Collider()
	{

	}

	const eCOLLIDER_TYPE& Collider::getType()
	{
		return m_Type;
	}

	const bool& Collider::isActive()
	{
		return m_bActive;
	}

	void Collider::setActive(bool _Boolean)
	{
		m_bActive = _Boolean;
	}

	const bool& Collider::Collide()
	{
		return m_bCollide;
	}

	void Collider::setCollide(bool _Boolean)
	{
		m_bCollide = _Boolean;
	}
}