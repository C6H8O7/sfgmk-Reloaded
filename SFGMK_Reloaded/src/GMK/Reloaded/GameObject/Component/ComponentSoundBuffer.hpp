#ifndef SFGMKR_COMPONENT_SOUND_BUFFER_HPP
#define SFGMKR_COMPONENT_SOUND_BUFFER_HPP

#include "stdafx.h"


class ComponentSoundBuffer : public GameObjectComponent
{
	friend class GameObject;

	public:
		ComponentSoundBuffer(GameObject* _parent);
		~ComponentSoundBuffer();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);
		virtual r_void OnDraw(SFMLCanvas* _canvas);

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	private:
		sf::SoundBuffer m_SoundBuffer;
		sf::Sound m_Sound;

		r_string m_SoundPath;
		r_bool m_bSoundPathChanged;

	public:
		r_void playSound();
		r_void stopSound();
};


#endif#