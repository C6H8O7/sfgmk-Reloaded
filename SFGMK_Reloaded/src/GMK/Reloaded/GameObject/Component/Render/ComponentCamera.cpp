#include "stdafx.h"

ComponentCamera::ComponentCamera(GameObject * _parent)
	: GameObjectComponent("Camera", _parent)
{
	m_Width = SFGMKR_DEFAULT_SFML_SIZE_X;
	m_Height = SFGMKR_DEFAULT_SFML_SIZE_Y;
	m_Zoom = 1.0f;

#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_SpriteInit = false;
}

ComponentCamera::~ComponentCamera()
{

}

r_void ComponentCamera::OnUpdate(SFMLCanvas * _canvas)
{
	if (!_canvas->isEditor())
	{
		m_View.setCenter(parent->transform.getPosition());
		m_View.setSize(r_vector2f(m_Width, m_Height));
		m_View.setRotation(parent->transform.getRotation());
		m_View.zoom(m_Zoom);

		_canvas->setView(m_View);
	}
}

r_void ComponentCamera::OnDraw(SFMLCanvas * _canvas)
{
#ifdef SFGMKR_EDITOR
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

		r_float w = m_Width * m_Zoom;
		r_float h = m_Height * m_Zoom;

		r_float sx = w / m_SpriteWidth;
		r_float sy = h / m_SpriteHeight;

		m_Sprite.setScale(sx, sy);
		m_Sprite.setPosition(parent->transform.getPosition());
		m_Sprite.setRotation(parent->transform.getRotation());

		_canvas->draw(m_Sprite);
	}
#endif
}

r_void ComponentCamera::OnMembersUpdate()
{

}

#ifdef SFGMKR_EDITOR
r_void ComponentCamera::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Width", &m_Width, &m_SizeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Height", &m_Height, &m_SizeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Zoom", &m_Zoom, &m_ZoomChanged);

	endRegister();
}
#endif

r_void ComponentCamera::OnXMLSave(tinyxml2::XMLElement * _element)
{
	_element->SetAttribute("width", m_Width);
	_element->SetAttribute("height", m_Height);
	_element->SetAttribute("zoom", m_Zoom);
}

r_void ComponentCamera::OnXMLLoad(tinyxml2::XMLElement * _element)
{
	m_Width = _element->FloatAttribute("width");
	m_Height = _element->FloatAttribute("height");
	m_SizeChanged = true;

	m_Zoom = _element->FloatAttribute("zoom");
	m_ZoomChanged = true;
}