#ifndef SFGMKR_COMPONENTTRANSFORM_HPP
#define SFGMKR_COMPONENTTRANSFORM_HPP

class ComponentTransform : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentTransform(GameObject* _parent);
	~ComponentTransform();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);
};

#endif