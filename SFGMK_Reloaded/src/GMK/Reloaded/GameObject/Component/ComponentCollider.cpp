ComponentCollider::ComponentCollider(GameObject* _parent)
	: GameObjectComponent("Collider", _parent), m_Collider(_parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_TypeChanged = false;
	m_SizeChanged = false;
}

ComponentCollider::~ComponentCollider()
{

}

r_void ComponentCollider::OnUpdate(SFMLCanvas * _canvas)
{
	if (parent->debug.collisionEnabled)
		m_Collider.setActive(true);
	else
		m_Collider.setActive(false);
}

r_void ComponentCollider::OnDraw(SFMLCanvas* _canvas)
{
#ifdef SFGMKR_EDITOR
	if (_canvas->isEditor())
		m_Collider.draw(_canvas);
#endif
}

r_void ComponentCollider::OnMembersUpdate()
{
	if (m_TypeChanged)
	{
		m_TypeChanged = false;

		m_Collider.setType(m_Type);
	}

	if (m_SizeChanged)
	{
		m_SizeChanged = false;

		m_Collider.setSize(r_vector2f(m_SizeX, m_SizeY));
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentCollider::OnRegistration()
{
	beginRegister();

	GameObjectComponent::ComponentProperty* propertyType = registerProperty(ePROPERTY_TYPE::TYPE_ENUM, "Type", &m_Type, &m_TypeChanged);
	propertyType->wxChoices.Add("Sphere", gmk::eCOLLIDER_TYPE::eSphere);
	propertyType->wxChoices.Add("OBB", gmk::eCOLLIDER_TYPE::eOBB);

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Size X", &m_SizeX, &m_SizeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Size Y", &m_SizeY, &m_SizeChanged);

	endRegister();
}
#endif

r_void ComponentCollider::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("ctype", (r_int32)m_Type);
	_element->SetAttribute("x", m_SizeX);
	_element->SetAttribute("y", m_SizeY);
}

r_void ComponentCollider::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Type = (gmk::eCOLLIDER_TYPE)_element->IntAttribute("ctype");
	m_TypeChanged = true;

	m_SizeX = _element->FloatAttribute("x");
	m_SizeY = _element->FloatAttribute("y");
	m_SizeChanged = true;
}

r_void ComponentCollider::setType(gmk::eCOLLIDER_TYPE _type)
{
	m_Type = _type;
	m_Collider.setType(_type);
}

r_void ComponentCollider::initType(gmk::eCOLLIDER_TYPE _type)
{
	m_Type = _type;
	m_Collider.setType(_type);

	m_SizeX = 32.0f;
	m_SizeY = 32.0f;
	m_Collider.setSize(r_vector2f(m_SizeX, m_SizeY));
}

gmk::Collider* ComponentCollider::getCollider()
{
	return &m_Collider;
}