#ifndef SFGMKR_COMPONENTGAMEOBJECT_HPP
#define SFGMKR_COMPONENTGAMEOBJECT_HPP

class ComponentGameObject : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentGameObject(GameObject* _parent);
	~ComponentGameObject();

	virtual void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual void OnRegistration();
#endif

	virtual void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual void OnXMLLoad(tinyxml2::XMLElement* _element);
};

#endif