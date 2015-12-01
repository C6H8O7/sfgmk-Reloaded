#ifndef SFGMKR_GAMEOBJECT_HPP
#define SFGMKR_GAMEOBJECT_HPP

class GameObject
{
public:

	GameObject();
	~GameObject();

	Transform transform;
	Transform* transformPtr;

	std::string name;

	void* treeID;

	void update(SFMLCanvas * _canvas);
	void draw(SFMLCanvas* _canvas);

	virtual void OnUpdate(SFMLCanvas * _canvas);
	virtual void OnDraw(SFMLCanvas* _canvas);

	sfgmk::vector<GameObjectComponent*>& getComponents();

	void addComponent(GameObjectComponent* _component);
	void removeComponent(GameObjectComponent* _component);

#ifdef SFGMKR_EDITOR
	void showComponents(bool _value);
	void updateComponents();

	static void AddAsComponent(GameObject* _object, std::string _componentPath);
#endif

private:

	sfgmk::vector<GameObjectComponent*> m_Components;
};

#endif