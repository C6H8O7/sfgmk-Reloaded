#ifndef SFGMKR_COMPONENTPARTICLESYSTEM_HPP
#define SFGMKR_COMPONENTPARTICLESYSTEM_HPP

class ComponentParticleSystem : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentParticleSystem(GameObject* _parent);
	~ComponentParticleSystem();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	ParticleSystem m_System;
	Particle** m_ParticlePtr;
};

#endif