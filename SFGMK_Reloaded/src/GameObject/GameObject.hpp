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

	void update();
	void draw();

	virtual void OnUpdate();
	virtual void OnDraw();

private:

	sfgmk::vector<GameObjectComponent*> m_Components;
};

#endif