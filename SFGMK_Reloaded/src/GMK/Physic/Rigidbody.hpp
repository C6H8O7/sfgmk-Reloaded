#ifndef SFGMKR_RIGIDBODY_HPP
#define SFGMKR_RIGIDBODY_HPP

#include "stdafx.h"

namespace gmk
{
	class Rigidbody
	{
	public:

		Rigidbody(GameObject* _parent);
		~Rigidbody();

		r_void update(float _deltaTime);

		r_void cleanForces();
		r_void addForce(r_vector2f _force);

		r_void cleanSpeed();

		GMK_CLASS_PROPERTY_FUNCS(r_float, m_maxForce, MaxForce, r_void)
		GMK_CLASS_PROPERTY_FUNCS(r_float, m_maxSpeed, MaxSpeed, r_void)

		GMK_CLASS_PROPERTY_FUNCS(r_vector2f, m_force, Force, r_void)
		GMK_CLASS_PROPERTY_FUNCS(r_vector2f, m_speed, Speed, r_void)

		GMK_CLASS_PROPERTY_FUNCS(r_vector2f, m_direction, Direction, r_void)

		GMK_CLASS_PROPERTY_FUNCS(r_bool, m_isGravityApplied, GravityApplied, r_void)
		GMK_CLASS_PROPERTY_FUNCS(r_vector2f, m_gravity, GravityForce, r_void)

	protected:

		GameObject* m_gameObject;

		r_float m_maxForce;
		r_float m_maxSpeed;

		r_vector2f m_force;
		r_vector2f m_speed;

		r_bool m_isGravityApplied;
		r_vector2f m_gravity;

		r_vector2f m_direction;
		r_vector2f m_previousPosition;
	};
}

#endif