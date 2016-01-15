#include "stdafx.h"

Transform::Transform() : rotation(0.0f), scale(1.0f, 1.0f), positionPtr(&position), scalePtr(&scale)
{

}

Transform::~Transform()
{

}