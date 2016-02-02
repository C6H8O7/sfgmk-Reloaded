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

	sf::Sprite* getSprite();

private:

	sf::Sprite m_Sprite;

	r_float m_OriginX;
	r_float m_OriginY;
	r_bool m_OriginChanged;

	sf::Color m_Color;
	r_bool m_ColorChanged;

	r_string m_Path;
	r_bool m_PathChanged;
};

#endif