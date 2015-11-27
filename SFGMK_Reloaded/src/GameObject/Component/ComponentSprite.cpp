ComponentSprite::ComponentSprite(GameObject* _parent)
	: GameObjectComponent("Sprite", _parent)
{
	OnRegistration();

	m_PathChanged = false;

	m_OriginX = 0.0f;
	m_OriginY = 0.0f;
	m_OriginChanged = false;
}

ComponentSprite::~ComponentSprite()
{

}

void ComponentSprite::OnUpdate()
{
	if (m_PathChanged)
	{
		m_PathChanged = false;

		m_Texture.loadFromFile(m_Path);
		m_Sprite.setTexture(m_Texture);
	}

	if (m_OriginChanged)
	{
		m_OriginChanged = false;

		m_Sprite.setOrigin(m_OriginX, m_OriginY);
	}

	m_Sprite.setPosition(parent->transform.position);
	m_Sprite.setScale(parent->transform.scale);
	m_Sprite.setRotation(parent->transform.rotation);
}

void ComponentSprite::OnDraw()
{
	sf::RenderWindow* render = MyGUI::GetGUI()->GUI_PreviewSFML;

	render->draw(m_Sprite);
}

void ComponentSprite::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Origin X", &m_OriginX, &m_OriginChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Origin Y", &m_OriginY, &m_OriginChanged);

	endRegister();
}