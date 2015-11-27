#ifndef SFGMKR_COMPONENTSPRITE_HPP
#define SFGMKR_COMPONENTSPRITE_HPP

class ComponentSprite : public GameObjectComponent
{
public:

	ComponentSprite(GameObject* _parent);
	~ComponentSprite();

	virtual void registration();
};

#endif