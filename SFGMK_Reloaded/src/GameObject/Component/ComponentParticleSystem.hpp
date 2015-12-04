#ifndef SFGMKR_COMPONENTPARTICLESYSTEM_HPP
#define SFGMKR_COMPONENTPARTICLESYSTEM_HPP

class ComponentParticleSystem : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentParticleSystem(GameObject* _parent);
	~ComponentParticleSystem();

	virtual void OnUpdate(SFMLCanvas * _canvas);
	virtual void OnDraw(SFMLCanvas* _canvas);

	virtual void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual void OnRegistration();
#endif

	virtual void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	ParticleSystem m_System;
	Particle** m_ParticlePtr;
};

#endif