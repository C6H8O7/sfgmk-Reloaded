ComponentSprite::ComponentSprite(GameObject* _parent)
	: GameObjectComponent("Sprite", _parent)
{
	OnRegistration();

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

void ComponentSprite::OnUpdate()
{
	if (m_PathChanged)
	{
		m_PathChanged = false;

		if(m_Texture.loadFromFile(m_Path))
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

	m_Sprite.setPosition(parent->transform.position);
	m_Sprite.setScale(parent->transform.scale);
	m_Sprite.setRotation(parent->transform.rotation);
}

void ComponentSprite::OnDraw(sf::RenderWindow* _render)
{
	_render->draw(m_Sprite);
}

void ComponentSprite::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Origin X", &m_OriginX, &m_OriginChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Origin Y", &m_OriginY, &m_OriginChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_COLOR, "Color", &m_Color, &m_ColorChanged);

	endRegister();
}