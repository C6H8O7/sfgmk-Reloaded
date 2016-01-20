#include "stdafx.h"


ComponentListener::ComponentListener(GameObject* _parent)
	: GameObjectComponent("Listener", _parent), m_GlobalVolume(100.0f), m_bGlobalVolumeChanged(false), m_Position(0.0f, 0.0f, 0.0f), m_bPositionChanged(false), m_Direction(1.0f, 0.0f, 0.0f), m_bDirectionChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	sf::Listener::setGlobalVolume(m_GlobalVolume);
	sf::Listener::setPosition(m_Position);
	sf::Listener::setDirection(m_Direction);

#ifdef SFGMKR_EDITOR
	m_Texture.loadFromFile("../data/editor/headset.png");
	m_Sprite.setTexture(m_Texture);
#endif
}

ComponentListener::~ComponentListener()
{
}


r_void ComponentListener::OnUpdate(SFMLCanvas * _canvas)
{
	sf::Listener::setPosition(parent->transform.position.x, parent->transform.position.y, 0.0f);
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
}


#ifdef SFGMKR_EDITOR
r_void ComponentListener::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "GlobalVolume", &m_GlobalVolume, &m_bGlobalVolumeChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Position X", &m_Position.x, &m_bPositionChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Position Y", &m_Position.x, &m_bPositionChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Direction X", &m_Direction.x, &m_bDirectionChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Position Y", &m_Direction.y, &m_bDirectionChanged);

	endRegister();
}

r_void ComponentListener::OnEditorUpdate()
{
	m_Sprite.setPosition(parent->transform.position.x, parent->transform.position.y);
}
#endif

r_void ComponentListener::OnXMLSave(tinyxml2::XMLElement* _element)
{
}

r_void ComponentListener::OnXMLLoad(tinyxml2::XMLElement* _element)
{
}