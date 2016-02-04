#ifndef SFGMKR_COMPONENTSTEERINGAGENT_HPP
#define SFGMKR_COMPONENTSTEERINGAGENT_HPP

#include "stdafx.h"

class ComponentSteeringAgent : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentSteeringAgent(GameObject* _parent);
	~ComponentSteeringAgent();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:
	gmk::Steering m_Steering;

#ifdef SFGMKR_EDITOR
	sf::VertexArray m_SteeringVectors;
#endif
};

#endif