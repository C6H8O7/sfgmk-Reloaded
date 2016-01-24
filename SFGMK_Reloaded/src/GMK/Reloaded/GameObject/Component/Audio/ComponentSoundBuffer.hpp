#ifndef SFGMKR_COMPONENT_SOUND_BUFFER_HPP
#define SFGMKR_COMPONENT_SOUND_BUFFER_HPP

#include "stdafx.h"


class ComponentSoundBuffer : public GameObjectComponent
{
	friend class GameObject;

	public:
		enum eAUDIO_TYPE
		{
			eSound = 0,
			eMusic,
			eAUDIO_TYPE_NUMBER
		};

		struct stSOUND_DATA
		{
			sf::SoundBuffer Buffer;
			r_string sPath;
		};

		struct stMUSIC_DATA
		{
			sf::Music Music;
			r_string sPath;
		};

		ComponentSoundBuffer(GameObject* _parent);
		~ComponentSoundBuffer();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);
		virtual r_void OnDraw(SFMLCanvas* _canvas);

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();

		r_void addRessourceEvent(wxEvent& _event);
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	private:
		std::map<r_string, stSOUND_DATA*> m_SoundBuffers;
		std::map<r_string, stMUSIC_DATA*> m_Musics;
		gmk::vector<sf::Sound*> m_Sounds;

		r_string m_Path;
		r_bool m_bPathChanged;

		eAUDIO_TYPE m_Type;
		r_bool m_TypeChanged;

		r_uint32 m_SoundNumber;
		r_uint32 m_MusicNumber;

	public:
		r_void addRessource();

		r_void playSound(const r_string& _Name);
		r_void playMusic(const r_string& _Name);
};


#endif