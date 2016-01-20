#include "stdafx.h"


ComponentListener::ComponentListener(GameObject* _parent)
	: GameObjectComponent("Listener", _parent), m_GlobalVolume(100.0f), m_bGlobalVolumeChanged(false), m_Position(0.0f, 0.0f, 0.0f), m_Direction(1.0f, 0.0f, 0.0f), m_bDirectionChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	sf::Listener::setGlobalVolume(m_GlobalVolume);
	sf::Listener::setPosition(m_Position);
	sf::Listener::setDirection(m_Direction);

#ifdef SFGMKR_EDITOR
	m_Texture.loadFromFile("../data/editor/headset.png");
	m_TextureSize = sf::Vector2f(m_Texture.getSize());
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setOrigin(m_TextureSize * 0.5f);
#endif
}

ComponentListener::~ComponentListener()
{
}


r_void ComponentListener::OnUpdate(SFMLCanvas * _canvas)
{
	r_vector2f ParentCenter = parent->getCenter();
	sf::Listener::setPosition((m_Position = r_vector3f(ParentCenter.x, ParentCenter.y, 0.0f)));

#ifdef SFGMKR_EDITOR
	m_Sprite.setPosition(ParentCenter);

	ComponentSprite* ParentSpriteComponent = NULL;
	if( (ParentSpriteComponent = (ComponentSprite*)parent->getComponent("Sprite")) )
	{
		sf::FloatRect ParentSpriteRect(ParentSpriteComponent->getSprite()->getGlobalBounds());
		m_Sprite.setPosition(ParentCenter + r_vector2f(0.0f, -ParentSpriteRect.height * 0.5f - m_TextureSize.y * 0.5f));
	}
#endif
}

r_void ComponentListener::OnDraw(SFMLCanvas* _canvas)
{
#ifdef SFGMKR_EDITOR
	if( _canvas->isEditor() )
		_canvas->draw(m_Sprite);
#endif
}


r_void ComponentListener::OnMembersUpdate()
{
	if( m_bGlobalVolumeChanged )
	{
		m_bGlobalVolumeChanged = false;
		sf::Listener::setGlobalVolume(m_GlobalVolume);
	}

	if( m_bDirectionChanged )
	{
		m_bDirectionChanged = false;
		sf::Listener::setDirection(m_Direction);
	}
}


#ifdef SFGMKR_EDITOR
r_void ComponentListener::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "GlobalVolume", &m_GlobalVolume, &m_bGlobalVolumeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Position X", &m_Position.x, 0, true);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Position Y", &m_Position.x, 0, true);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Direction X", &m_Direction.x, &m_bDirectionChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Direction Y", &m_Direction.y, &m_bDirectionChanged);

	endRegister();
}
#endif

r_void ComponentListener::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("GlobalVolume", m_GlobalVolume);
	_element->SetAttribute("DirectionX", m_Direction.x);
	_element->SetAttribute("DirectionY", m_Direction.y);
	_element->SetAttribute("DirectionZ", m_Direction.z);
}

r_void ComponentListener::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_GlobalVolume = _element->FloatAttribute("GlobalVolume");
	m_bGlobalVolumeChanged = true;

	m_Direction.x = _element->FloatAttribute("DirectionX");
	m_Direction.y = _element->FloatAttribute("DirectionY");
	m_Direction.z = _element->FloatAttribute("DirectionZ");
	m_bDirectionChanged = true;
}