#ifndef SFGMKR_GAMEOBJECTCOMPONENT_HPP
#define SFGMKR_GAMEOBJECTCOMPONENT_HPP

class GameObject;

class GameObjectComponent
{
public:

	GameObjectComponent(GameObject* _parent);
	~GameObjectComponent();

	virtual void OnUpdate() = 0;
	virtual void OnDraw() = 0;

	GameObject* parent;

	bool active;

	std::string type;
};

#endif