#ifndef SFGMKR_GAMEOBJECT_HPP
#define SFGMKR_GAMEOBJECT_HPP

class GameObject
{
public:

	GameObject(bool _createDefault = true);
	~GameObject();

	Transform transform;
	Transform* transformPtr;

	std::string name;

	void* treeID;

	void update(SFMLCanvas * _canvas);
	void draw(SFMLCanvas* _canvas);

	gmk::vector<GameObjectComponent*>& getComponents();

	void addComponent(GameObjectComponent* _component);
	void removeComponent(GameObjectComponent* _component);

#ifdef SFGMKR_EDITOR
	void showComponents(bool _value);
	void updateComponents();

	static void AddAsComponent(GameObject* _object, std::string _componentPath);

	virtual void OnEditorUpdate();
#endif

private:

	gmk::vector<GameObjectComponent*> m_Components;
};

#endif