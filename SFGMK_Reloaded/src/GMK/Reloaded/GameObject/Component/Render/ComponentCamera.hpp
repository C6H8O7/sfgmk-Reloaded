#ifndef SFGMKR_COMPONENTCAMERA_HPP
#define SFGMKR_COMPONENTCAMERA_HPP

#include "stdafx.h"

class ComponentCamera : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentCamera(GameObject* _parent);
	~ComponentCamera();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	r_float m_Width, m_Height;
	r_bool m_SizeChanged;

	r_float m_Zoom;
	r_bool m_ZoomChanged;

	r_float m_SpriteWidth, m_SpriteHeight;
	r_bool m_SpriteInit;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	sf::View m_View;
};

#endif