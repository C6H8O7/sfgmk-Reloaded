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
	void draw(sf::RenderWindow* _render);

	virtual void OnUpdate();
	virtual void OnDraw(sf::RenderWindow* _render);

	sfgmk::vector<GameObjectComponent*>& getComponents();

	void addComponent(GameObjectComponent* _component);

	void showComponents(bool _value);
	void updateComponents();

private:

	sfgmk::vector<GameObjectComponent*> m_Components;
};

#endif