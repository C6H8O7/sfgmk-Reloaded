#include "stdafx.h"


ComponentSoundBuffer::ComponentSoundBuffer(GameObject* _parent)
	: GameObjectComponent("SoundBuffer", _parent), m_SoundPath(""), m_bSoundPathChanged(false)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	m_Sound.setBuffer(m_SoundBuffer);

	parent->soundBufferPtr = this;
}

ComponentSoundBuffer::~ComponentSoundBuffer()
{
	m_Sound.stop();
}


r_void ComponentSoundBuffer::OnUpdate(SFMLCanvas * _canvas)
{
}

r_void ComponentSoundBuffer::OnDraw(SFMLCanvas* _canvas)
{
}


r_void ComponentSoundBuffer::OnMembersUpdate()
{
	if( m_bSoundPathChanged )
	{
		m_bSoundPathChanged = false;
		m_SoundBuffer.loadFromFile(gmk::AssetsManager::GetSingleton()->getAssetPath(m_SoundPath));
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentSoundBuffer::OnRegistration()
{
	beginRegister();
	
	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Sound", &m_SoundPath, &m_bSoundPathChanged);

	endRegister();
}

#endif

r_void ComponentSoundBuffer::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("SoundPath", m_SoundPath.c_str());
}

r_void ComponentSoundBuffer::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_SoundPath = _element->Attribute("SoundPath");
	m_bSoundPathChanged = true;
}


r_void ComponentSoundBuffer::playSound()
{
	m_Sound.stop();
	m_Sound.play();
}

r_void ComponentSoundBuffer::stopSound()
{
	m_Sound.stop();
}