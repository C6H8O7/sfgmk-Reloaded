ComponentSprite::ComponentSprite(GameObject* _parent)
	: GameObjectComponent("Sprite", _parent)
{
	OnRegistration();

	m_PathChanged = false;
}

ComponentSprite::~ComponentSprite()
{

}

void ComponentSprite::OnUpdate()
{
	if (m_PathChanged)
	{
		m_Texture.loadFromFile(m_Path);
		m_Sprite.setTexture(m_Texture);
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

	endRegister();
}