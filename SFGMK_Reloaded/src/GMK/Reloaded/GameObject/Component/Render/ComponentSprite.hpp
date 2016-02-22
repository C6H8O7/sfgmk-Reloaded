#ifndef SFGMKR_COMPONENTSPRITE_HPP
#define SFGMKR_COMPONENTSPRITE_HPP

#include "stdafx.h"

class ComponentSprite : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentSprite(GameObject* _parent);
	~ComponentSprite();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	gmk::Sprite* getSprite();

private:

	gmk::Sprite m_Sprite;

	r_float m_OriginX = 0.0f;
	r_float m_OriginY = 0.0f;
	r_bool m_OriginChanged = false;

	sf::Color m_Color = sf::Color::White;
	r_bool m_ColorChanged = false;

	r_string m_Path;
	r_bool m_PathChanged = false;
};

#endif