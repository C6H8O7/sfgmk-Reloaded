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

	sfgmk::vector<GameObjectComponent*>& getComponents();

	void addComponent(GameObjectComponent* _component);

	void showComponents(bool _value);

private:

	sfgmk::vector<GameObjectComponent*> m_Components;
};

#endif