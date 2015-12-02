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
};

#endif