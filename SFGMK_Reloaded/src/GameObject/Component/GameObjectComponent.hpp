#ifndef SFGMKR_GAMEOBJECTCOMPONENT_HPP
#define SFGMKR_GAMEOBJECTCOMPONENT_HPP

class GameObject;

class GameObjectComponent
{
protected:

	enum ePROPERTY_TYPE
	{
		TYPE_STRING,
		TYPE_INT,
		TYPE_FLOAT
	};

	void beginRegister();
	void registerProperty();
	void endRegister();

public:

	GameObjectComponent(GameObject* _parent);
	~GameObjectComponent();

	virtual void OnUpdate() = 0;
	virtual void OnDraw() = 0;

	virtual void OnRegistration() = 0;

	GameObject* parent;

	bool active;

	std::string type;
	bool unique;
};

#endif