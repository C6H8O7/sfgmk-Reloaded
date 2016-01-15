#include "stdafx.h"

namespace gmk
{
	SphereCollider::SphereCollider(GameObject* _gameobject)
		: Collider(_gameobject)
	{
		m_Type = eCOLLIDER_TYPE::eSphere;
	}

	SphereCollider::~SphereCollider()
	{

	}

	r_float SphereCollider::getRadius()
	{
		return m_Size.x * m_GameObject->transform.scale.x;
	}

	r_float SphereCollider::getSquaredRadius()
	{
		r_float r = getRadius();

		return r * r;
	}
}