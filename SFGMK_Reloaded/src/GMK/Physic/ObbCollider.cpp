#include "stdafx.h"

namespace gmk
{
	ObbCollider::ObbCollider(GameObject* _gameobject)
		: Collider(_gameobject)
	{
		m_Type = eCOLLIDER_TYPE::eOBB;
	}

	ObbCollider::~ObbCollider()
	{

	}

	r_float ObbCollider::getRadius()
	{
		return MAX(m_Size.x * m_GameObject->transform.getScale().x, m_Size.y * m_GameObject->transform.getScale().y);
	}

	r_float ObbCollider::getSquaredRadius()
	{
		r_float radius = getRadius();

		return radius * radius;
	}

	r_vector2f ObbCollider::getMin()
	{
		return r_vector2f();
	}

	r_vector2f ObbCollider::getMax()
	{
		return m_Size;
	}

	r_vector2f ObbCollider::getRight()
	{
		r_float fAngle = DEG_TO_RAD(m_GameObject->transform.getRotation());

		return math::MatrixRotation22(fAngle) * X_UNIT_VECTOR_2D;
	}

	r_vector2f ObbCollider::getUp()
	{
		r_float fAngle = DEG_TO_RAD(m_GameObject->transform.getRotation());

		return math::MatrixRotation22(fAngle) * Y_UNIT_VECTOR_2D;
	}
}