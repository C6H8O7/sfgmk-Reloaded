#ifndef SFGMKR_COMPONENTLISTENER_HPP
#define SFGMKR_COMPONENTLISTENER_HPP

#include "stdafx.h"


class ComponentListener : public GameObjectComponent
{
	friend class GameObject;

	public:
		ComponentListener(GameObject* _parent);
		~ComponentListener();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);
		virtual r_void OnDraw(SFMLCanvas* _canvas);

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	private:
		r_float m_GlobalVolume;
		r_bool m_bGlobalVolumeChanged;

		r_vector3f m_Position, m_Direction;
		r_bool m_bDirectionChanged;

#ifdef SFGMKR_EDITOR
		sf::Texture m_Texture;
		sf::Vector2f m_TextureSize;
		sf::Sprite m_Sprite;
#endif
};


#endif