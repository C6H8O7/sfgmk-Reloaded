#ifndef SFGMKR_COMPONENTTEXT_HPP
#define SFGMKR_COMPONENTTEXT_HPP

#include "stdafx.h"

class ComponentText : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentText(GameObject* _parent);
	~ComponentText();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	r_string m_FontPath;
	r_bool m_FontPathChanged;

	r_int32 m_Size;

	sf::Color m_Color;

	sf::Text m_TextRenderer;
};

#endif