ComponentCamera::ComponentCamera(GameObject * _parent)
	: GameObjectComponent("Camera", _parent)
{
	m_Width = SFGMKR_DEFAULT_SFML_SIZE_X;
	m_Height = SFGMKR_DEFAULT_SFML_SIZE_Y;
	m_Zoom = 1.0f;

	OnRegistration();

	m_SpriteInit = false;
}

ComponentCamera::~ComponentCamera()
{

}

void ComponentCamera::OnUpdate(SFMLCanvas * _canvas)
{
	if (!_canvas->isEditor())
	{
		m_View.setCenter(parent->transform.position);
		m_View.setSize(sf::Vector2f(m_Width, m_Height));
		m_View.setRotation(parent->transform.rotation);
		m_View.zoom(m_Zoom);

		_canvas->setView(m_View);
	}
}

void ComponentCamera::OnDraw(SFMLCanvas * _canvas)
{
	if (_canvas->isEditor())
	{
		if (!m_SpriteInit)
		{
			m_SpriteInit = true;

			m_Texture.loadFromFile("../data/editor/camera.png");
			m_Sprite.setTexture(m_Texture);

			m_SpriteWidth = m_Sprite.getLocalBounds().width;
			m_SpriteHeight = m_Sprite.getLocalBounds().height;

			m_Sprite.setOrigin(m_SpriteWidth / 2.0f, m_SpriteHeight / 2.0f);
		}

		float w = m_Width * m_Zoom;
		float h = m_Height * m_Zoom;

		float sx = w / m_SpriteWidth;
		float sy = h / m_SpriteHeight;

		m_Sprite.setScale(sx, sy);
		m_Sprite.setPosition(parent->transform.position);
		m_Sprite.setRotation(-parent->transform.rotation);

		_canvas->draw(m_Sprite);
	}
}

#ifdef SFGMKR_EDITOR
void ComponentCamera::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Width", &m_Width, &m_SizeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Height", &m_Height, &m_SizeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Zoom", &m_Zoom, &m_ZoomChanged);

	endRegister();
}
#endif

void ComponentCamera::OnXMLSave(tinyxml2::XMLElement * _element)
{
	_element->SetAttribute("width", m_Width);
	_element->SetAttribute("height", m_Height);
	_element->SetAttribute("zoom", m_Zoom);
}

void ComponentCamera::OnXMLLoad(tinyxml2::XMLElement * _element)
{
	m_Width = _element->FloatAttribute("width");
	m_Height = _element->FloatAttribute("height");
	m_SizeChanged = true;

	m_Zoom = _element->FloatAttribute("zoom");
	m_ZoomChanged = true;
}