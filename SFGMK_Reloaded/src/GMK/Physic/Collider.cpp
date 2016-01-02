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
}