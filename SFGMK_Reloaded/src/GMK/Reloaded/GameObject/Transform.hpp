#ifndef SFGMKR_TRANSFORM_HPP
#define SFGMKR_TRANSFORM_HPP

class Transform
{
public:

	Transform();
	~Transform();

	float rotation;
	sf::Vector2f position, scale;

	sf::Vector2f *positionPtr, *scalePtr;
};

#endif