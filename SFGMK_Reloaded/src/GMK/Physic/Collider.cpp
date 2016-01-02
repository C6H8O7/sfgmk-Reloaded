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

	const r_bool& Collider::isActive()
	{
		return m_bActive;
	}

	r_void Collider::setActive(r_bool _Boolean)
	{
		m_bActive = _Boolean;
	}

	const r_bool& Collider::Collide()
	{
		return m_bCollide;
	}

	r_void Collider::setCollide(r_bool _Boolean)
	{
		m_bCollide = _Boolean;
	}
}