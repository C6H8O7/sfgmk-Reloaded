#ifndef SFGMKR_GAMEOBJECT_HPP
#define SFGMKR_GAMEOBJECT_HPP

class GameObject
{
public:

	GameObject();
	~GameObject();

	Transform transform;

	std::string name;
};

#endif