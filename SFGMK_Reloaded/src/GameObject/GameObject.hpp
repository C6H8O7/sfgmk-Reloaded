#ifndef SFGMKR_GAMEOBJECT_HPP
#define SFGMKR_GAMEOBJECT_HPP

class GameObject
{
public:

	GameObject();
	~GameObject();

	Transform transform;

	std::string name;

	void* treeID;

private:

	sfgmk::vector<GameObjectComponent*> m_Components;
};

#endif