#ifndef SFGMKR_PARTICLE_HPP
#define SFGMKR_PARTICLE_HPP

struct Particle
{
	Particle(sf::Vector2f& _position = sf::Vector2f(), float _mass = 1.0f)
		: position(_position), mass(_mass), massinv(1.0f / _mass)
	{

	}

	sf::Vector2f position;
	sf::Vector2f speed;
	sf::Vector2f force;

	float mass, massinv;

	float lifetime, lifetimeinv, lifetimer;

	inline void update(float& _timeDelta)
	{
													// F = ma <=> a = F/m
		speed += force * massinv * _timeDelta;		// v = v + dv avec dv = a * dt
		position += speed * _timeDelta;				// p = p + dp avec dp = v * dt
	}

	inline void reset(sf::Vector2f& _position)
	{
		float angle = (rand() % 3600) / 10.0f;
		angle = angle * 3.14f / 180.0f;

		sf::Vector2f newspeed(cosf(angle), sinf(angle));
		newspeed *= (float)(rand() % 100 + 100);

		lifetime = (float)(rand() % 50000 + 50000) / 10000.0f;
		lifetimeinv = 1.0f / lifetime;
		lifetimer = 0.0f;

		speed = newspeed;

		position = _position;
	}
};

#endif