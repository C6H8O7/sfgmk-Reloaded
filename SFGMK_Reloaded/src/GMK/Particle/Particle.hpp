#ifndef SFGMKR_PARTICLE_HPP
#define SFGMKR_PARTICLE_HPP

struct Particle
{
	Particle(r_vector2f& _position = r_vector2f(), r_float _mass = 1.0f)
		: position(_position), mass(_mass), massinv(1.0f / _mass)
	{

	}

	r_vector2f position;
	r_vector2f speed;
	r_vector2f force;

	r_float mass, massinv;

	r_float lifetime, lifetimeinv, lifetimer;

	inline r_void update(r_float& _timeDelta)
	{
													// F = ma <=> a = F/m
		speed += force * massinv * _timeDelta;		// v = v + dv avec dv = a * dt
		position += speed * _timeDelta;				// p = p + dp avec dp = v * dt
	}

	inline r_void reset(r_vector2f& _position)
	{
		r_float angle = (rand() % 3600) / 10.0f;
		angle = angle * 3.14f / 180.0f;

		r_vector2f newspeed(cosf(angle), sinf(angle));
		newspeed *= (r_float)(rand() % 100 + 100);

		lifetime = (r_float)(rand() % 50000 + 50000) / 10000.0f;
		lifetimeinv = 1.0f / lifetime;
		lifetimer = 0.0f;

		speed = newspeed;

		position = _position;
	}
};

#endif