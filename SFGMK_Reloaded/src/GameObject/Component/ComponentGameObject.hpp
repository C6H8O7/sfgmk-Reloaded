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
};

#endif