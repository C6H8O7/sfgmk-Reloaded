ComponentSprite::ComponentSprite(GameObject* _parent)
	: GameObjectComponent("Sprite", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_PathChanged = false;

	m_OriginX = 0.0f;
	m_OriginY = 0.0f;
	m_OriginChanged = false;

	m_Color = sf::Color::White;
	m_ColorChanged = false;
}

ComponentSprite::~ComponentSprite()
{

}

r_void ComponentSprite::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentSprite::OnDraw(SFMLCanvas* _canvas)
{
	m_Sprite.setPosition(parent->transform.position);
	m_Sprite.setScale(parent->transform.scale);
	m_Sprite.setRotation(parent->transform.rotation);

	_canvas->draw(m_Sprite);
}

r_void ComponentSprite::OnMembersUpdate()
{
	if (m_PathChanged)
	{
		m_PathChanged = false;

		if (m_Path.size() && m_Texture.loadFromFile(gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path)))
			m_Sprite.setTexture(m_Texture);
	}

	if (m_OriginChanged)
	{
		m_OriginChanged = false;

		m_Sprite.setOrigin(m_OriginX, m_OriginY);
	}

	if (m_ColorChanged)
	{
		m_Sprite.setColor(m_Color);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSprite::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Origin X", &m_OriginX, &m_OriginChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Origin Y", &m_OriginY, &m_OriginChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_COLOR, "Color", &m_Color, &m_ColorChanged);

	endRegister();
}
#endif

r_void ComponentSprite::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("path", m_Path.c_str());

	_element->SetAttribute("origin_x", m_OriginX);
	_element->SetAttribute("origin_y", m_OriginY);

	_element->SetAttribute("r", m_Color.r);
	_element->SetAttribute("g", m_Color.g);
	_element->SetAttribute("b", m_Color.b);
	_element->SetAttribute("a", m_Color.a);
}

r_void ComponentSprite::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Path = _element->Attribute("path");
	m_PathChanged = true;

	m_OriginX = _element->FloatAttribute("origin_x");
	m_OriginY = _element->FloatAttribute("origin_y");
	m_OriginChanged = true;

	m_Color = sf::Color(_element->IntAttribute("r"), _element->IntAttribute("g"), _element->IntAttribute("b"), _element->IntAttribute("a"));
	m_ColorChanged = true;
}

sf::Sprite* ComponentSprite::getSprite()
{
	return &m_Sprite;
}