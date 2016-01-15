#ifndef SFGMKR_TRANSFORM_HPP
#define SFGMKR_TRANSFORM_HPP

#include "stdafx.h"

class Transform
{
public:

	Transform();
	~Transform();

	r_float rotation;
	r_vector2f position, scale;

	r_vector2f *positionPtr, *scalePtr;
};

#endif