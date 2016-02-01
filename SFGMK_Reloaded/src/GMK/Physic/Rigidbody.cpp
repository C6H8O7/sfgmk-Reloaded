#include "stdafx.h"

namespace gmk
{
	Rigidbody::Rigidbody(GameObject* _parent)
		: m_gameObject(_parent)
	{
		m_force = m_speed = r_vector2f(0.0f, 0.0f);
		m_position = m_gameObject->transform.position;

		m_isGravityApplied = true;
		m_gravity = r_vector2f(0.0f, -gmk::math::G);

		m_maxForce = m_maxSpeed = -1.0f;
	}

	Rigidbody::~Rigidbody()
	{

	}

	r_void Rigidbody::update(float _deltaTime)
	{
		if (m_isGravityApplied)
			m_force += m_gravity * _deltaTime;

		if(m_maxForce >= 0.0f)
			m_force = math::Clamp_Vector(m_force, 0.0f, m_maxForce);

		m_speed += m_force * _deltaTime;

		if (m_maxSpeed >= 0.0f)
			m_speed = math::Clamp_Vector(m_speed, 0.0f, m_maxSpeed);

		m_position += m_speed * _deltaTime;

		m_gameObject->transform.position = m_position;
	}

	r_void Rigidbody::cleanForces()
	{
		m_force.x = m_force.y = 0.0f;
	}

	r_void Rigidbody::addForce(r_vector2f _force)
	{
		m_force += _force;
	}

	r_void Rigidbody::cleanSpeed()
	{
		m_speed.x = m_speed.y = 0.0f;
	}
}