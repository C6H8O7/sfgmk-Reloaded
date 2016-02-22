#include "stdafx.h"

ComponentSprite::ComponentSprite(GameObject* _parent)
	: GameObjectComponent("Sprite", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentSprite::~ComponentSprite()
{

}

r_void ComponentSprite::OnUpdate(SFMLCanvas * _canvas)
{
#ifdef SFGMKR_EDITOR
	if (_canvas->isEditor())
		return;
#endif
	if (!_canvas->isPlaying)
		return;

	r_float timeDelta = gmk::TimeManager::GetSingleton()->getDeltaTime();

	m_Sprite.finalize(timeDelta);
}

r_void ComponentSprite::OnDraw(SFMLCanvas* _canvas)
{
	m_Sprite.setPosition(parent->transform.getPosition());
	m_Sprite.setScale(parent->transform.getScale());
	m_Sprite.setRotation(parent->transform.getRotation());

	sf::RenderStates states;
	if (ComponentShader* ShaderComponent = (ComponentShader*)parent->getComponent("Shader"))
		states.shader = ShaderComponent->getShader();

	_canvas->draw(m_Sprite, states);
}

r_void ComponentSprite::OnMembersUpdate()
{
	if (m_PathChanged)
	{
		m_PathChanged = false;

		if (m_Path.size() && m_Path.find(".anim") == r_string::npos)
			m_Sprite.setTexture(gmk::AssetsManager::GetSingleton()->getTexture(m_Path), true);
		else if (m_Path.size())
			m_Sprite.setAnimation(gmk::AssetsManager::GetSingleton()->getSpriteAnimation(m_Path));
	}

	if (m_OriginChanged)
	{
		m_OriginChanged = false;
		m_Sprite.setOrigin(m_OriginX, m_OriginY);

		parent->transform.setOrigin(m_OriginX, m_OriginY);
	}

	if (m_ColorChanged)
	{
		m_ColorChanged = false;
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

gmk::Sprite* ComponentSprite::getSprite()
{
	return &m_Sprite;
}