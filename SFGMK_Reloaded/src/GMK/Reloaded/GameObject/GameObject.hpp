#ifndef SFGMKR_GAMEOBJECT_HPP
#define SFGMKR_GAMEOBJECT_HPP

class GameObject
{
public:

	GameObject(r_bool _createDefault = true);
	~GameObject();

	Transform transform;
	Transform* transformPtr;

	gmk::PathfindingAgent* pathfindingPtr;

	r_string name;

	r_void* treeID;

	r_void update(SFMLCanvas * _canvas);
	r_void draw(SFMLCanvas* _canvas);

	gmk::vector<GameObjectComponent*>& getComponents();

	r_void addComponent(GameObjectComponent* _component);
	r_void removeComponent(GameObjectComponent* _component);

	GameObjectComponent* getComponent(r_string _name);
	gmk::vector<GameObjectComponent*> getComponents(r_string _name);

#ifdef SFGMKR_EDITOR
	r_void showComponents(r_bool _value);
	r_void updateComponents();

	static r_void AddAsComponent(GameObject* _object, r_string _componentPath);
#endif

	r_void onPhysicEnter();
	r_void onPhysicCollision(GameObject* _object);
	r_void onPhysicExit();

	r_void registerScript(ComponentScript* _component);
	r_void unregisterScript(ComponentScript* _component);

	sf::Transform getTransform();

	r_vector2f getCenter();

private:

	gmk::vector<GameObjectComponent*> m_Components;

	gmk::vector<ComponentScript*> m_Scripts;
};

#endif