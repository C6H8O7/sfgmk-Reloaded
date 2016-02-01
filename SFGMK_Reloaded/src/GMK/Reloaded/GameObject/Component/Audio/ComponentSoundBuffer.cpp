#include "stdafx.h"


ComponentSoundBuffer::ComponentSoundBuffer(GameObject* _parent)
	: GameObjectComponent("SoundBuffer", _parent), m_Path(""), m_bPathChanged(false), m_Type(eSound), m_TypeChanged(false), m_SoundNumber(0U), m_MusicNumber(0U)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	parent->soundBufferPtr = this;
}

ComponentSoundBuffer::~ComponentSoundBuffer()
{
	for( r_uint32 i(0U); i < m_Sounds.size(); i++ )
		m_Sounds[i]->stop();
	m_Sounds.deleteAndClear();

	for( auto it = m_SoundBuffers.begin(); it != m_SoundBuffers.end(); ++it )
		delete (*it).second;
	m_SoundBuffers.clear();

	for( auto it = m_Musics.begin(); it != m_Musics.end(); ++it )
		delete (*it).second;
	m_Musics.clear();
}


r_void ComponentSoundBuffer::OnUpdate(SFMLCanvas * _canvas)
{
	for( r_uint32 i(0U); i < m_Sounds.size(); i++ )
	{
		if( m_Sounds[i]->getStatus() == sf::Sound::Status::Stopped )
		{
			delete m_Sounds[i];
			m_Sounds.removeElementByIndex(i);
		}
	}
}

r_void ComponentSoundBuffer::OnDraw(SFMLCanvas* _canvas)
{
}


r_void ComponentSoundBuffer::OnMembersUpdate()
{
}

#ifdef SFGMKR_EDITOR
r_void ComponentSoundBuffer::OnRegistration()
{
	beginRegister();
	
	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Ressource", &m_Path, &m_bPathChanged);

	GameObjectComponent::ComponentProperty* propertyType = registerProperty(ePROPERTY_TYPE::TYPE_ENUM, "Ressource Type", &m_Type, &m_TypeChanged);
	propertyType->wxChoices.Add("Sound", eAUDIO_TYPE::eSound);
	propertyType->wxChoices.Add("Music", eAUDIO_TYPE::eMusic);

	registerProperty(ePROPERTY_TYPE::TYPE_BUTTON, "Add Ressource", 0, 0, false, (wxObjectEventFunction)&ComponentSoundBuffer::addRessourceEvent);
	registerProperty(ePROPERTY_TYPE::TYPE_BUTTON, "Remove Ressource", 0, 0, false, (wxObjectEventFunction)&ComponentSoundBuffer::removeRessourceEvent);

	r_uint32 uiMusicIndex(0U);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Music Bank:", &m_MusicNumber, 0, true);
	for( auto it = m_Musics.begin(); it != m_Musics.end(); ++it )
	{
		registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Music Name " + std::to_string(uiMusicIndex), (r_void*)&((*it).first), 0, true);
		uiMusicIndex++;
	}

	r_uint32 uiSoundIndex(0U);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Sound Bank:", &m_SoundNumber, 0, true);
	for( auto it = m_SoundBuffers.begin(); it != m_SoundBuffers.end(); ++it )
	{
		registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Sound Name " + std::to_string(uiSoundIndex), (r_void*)&((*it).first), 0, true);
		uiSoundIndex++;
	}

	endRegister();
}
#endif

r_void ComponentSoundBuffer::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("Music_Number", (r_uint32)m_MusicNumber);
	_element->SetAttribute("Sound_Number", (r_uint32)m_SoundNumber);

	for( auto it = m_Musics.begin(); it != m_Musics.end(); ++it )
	{
		tinyxml2::XMLElement* elemVariable = _element->GetDocument()->NewElement("Music");
		elemVariable->SetAttribute("Path", (*(r_string*)&(*it).second->sPath).c_str());
		_element->LinkEndChild(elemVariable);
	}

	for( auto it = m_SoundBuffers.begin(); it != m_SoundBuffers.end(); ++it )
	{
		tinyxml2::XMLElement* elemVariable = _element->GetDocument()->NewElement("Sound");
		elemVariable->SetAttribute("Path", (*(r_string*)&(*it).second->sPath).c_str());
		_element->LinkEndChild(elemVariable);
	}
}

r_void ComponentSoundBuffer::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	r_uint32 MusicNumber = (r_uint32)_element->IntAttribute("Music_Number");
	r_uint32 SoundNumber = (r_uint32)_element->IntAttribute("Sound_Number");

	tinyxml2::XMLElement* elemVariable = _element->FirstChildElement("Music");
	if( elemVariable )
	{
		for( r_uint32 i(0U); i < MusicNumber; i++ )
		{
			m_Path = elemVariable->Attribute("Path");
			m_Type = eMusic;
			addRessource();
			elemVariable = elemVariable->NextSiblingElement("Music");
		}
	}
	
	elemVariable = _element->FirstChildElement("Sound");
	if( elemVariable )
	{
		for( r_uint32 i(0U); i < SoundNumber; i++ )
		{
			m_Path = elemVariable->Attribute("Path");
			m_Type = eSound;
			addRessource();
			elemVariable = elemVariable->NextSiblingElement("Sound");
		}
	}

	m_Path = "";
}


#ifdef SFGMKR_EDITOR
r_void ComponentSoundBuffer::addRessourceEvent(wxEvent& _event)
{
	addRessource();
}

r_void ComponentSoundBuffer::removeRessourceEvent(wxEvent& _event)
{
	std::map<r_string, stSOUND_DATA*>::iterator SoundIterator;
	std::map<r_string, stMUSIC_DATA*>::iterator MusicIterator;
	r_bool bDelete(false);

	switch( m_Type )
	{
		case eSound:
			if( (SoundIterator = m_SoundBuffers.find(m_Path)) != m_SoundBuffers.end() )
			{
				delete (*SoundIterator).second;
				m_SoundBuffers.erase(SoundIterator);
				m_SoundNumber--;
				bDelete = true;
			}
			break;

		case eMusic:
			if( (MusicIterator = m_Musics.find(m_Path)) != m_Musics.end() )
			{
				delete (*MusicIterator).second;
				m_Musics.erase(MusicIterator);
				m_MusicNumber--;
				bDelete = true;
			}
			break;

		default:
			break;
	}

	if( bDelete )
	{
		parent->showComponents(false);

		unregisterProperties();
		OnRegistration();

		parent->showComponents(true);
	}
}
#endif

r_void ComponentSoundBuffer::addRessource()
{
	stSOUND_DATA* NewSound(NULL);
	stMUSIC_DATA* NewMusic(NULL);

	r_string DataPath = gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path);
	r_string sName(DataPath);
	sName = sName.substr(0, sName.find_last_of('.', sName.length()));
	sName = sName.substr(sName.find_last_of('/', sName.length()) + 1, sName.length());

	switch( m_Type )
	{
		case eSound:
			if( m_SoundBuffers.find(sName) == m_SoundBuffers.end() )
			{
				NewSound = new stSOUND_DATA;
				NewSound->sPath = m_Path;
				if( NewSound->Buffer.loadFromFile(DataPath) )
				{
					m_SoundBuffers[sName] = NewSound;
					m_SoundNumber++;
				}
			}
			break;

		case eMusic:
			if( m_Musics.find(sName) == m_Musics.end() )
			{
				NewMusic = new stMUSIC_DATA;
				NewMusic->sPath = m_Path;
				if( NewMusic->Music.openFromFile(DataPath) )
				{
					m_Musics[sName] = NewMusic;
					m_MusicNumber++;
				}
			}
			break;

		default:
#ifdef SFGMKR_SOUND_DEBUG
			gmk::Debug::Log("[ERROR] SoundBuffer : bad type specified");
#endif
			break;
	}

#ifdef SFGMKR_EDITOR
	OnPropertiesReload();
#endif
}


r_bool ComponentSoundBuffer::playSound(const r_string& _Name)
{
	auto it = m_SoundBuffers.find(_Name);
	if( it != m_SoundBuffers.end() )
	{
		sf::Sound* NewSound = new sf::Sound((*it).second->Buffer);
		m_Sounds.push_back(NewSound);
		NewSound->play();
		return true;
	}

	return false;
}


r_bool ComponentSoundBuffer::playMusic(const r_string& _Name)
{
	auto it = m_Musics.find(_Name);
	if( it != m_Musics.end() )
	{
		(*it).second->Music.play();
		return true;
	}

	return false;
}

r_void ComponentSoundBuffer::stopMusic(const r_string& _Name)
{
	auto it = m_Musics.find(_Name);
	if( it != m_Musics.end() )
		(*it).second->Music.stop();
}