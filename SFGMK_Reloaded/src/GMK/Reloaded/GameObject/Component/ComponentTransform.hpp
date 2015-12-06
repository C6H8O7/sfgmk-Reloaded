#ifndef SFGMKR_COMPONENTTRANSFORM_HPP
#define SFGMKR_COMPONENTTRANSFORM_HPP

class ComponentTransform : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentTransform(GameObject* _parent);
	~ComponentTransform();

#ifdef SFGMKR_EDITOR
	virtual void OnRegistration();
#endif

	virtual void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual void OnXMLLoad(tinyxml2::XMLElement* _element);
};

#endif