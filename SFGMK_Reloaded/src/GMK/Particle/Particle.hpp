#ifndef SFGMKR_PARTICLE_HPP
#define SFGMKR_PARTICLE_HPP

class Particle
{
public:

	Particle(sf::Vector2f& _position = sf::Vector2f(), float _mass = 1.0f);
	~Particle();

	sf::Vector2f position;
	sf::Vector2f speed;
	sf::Vector2f acceleration;
	sf::Vector2f force;

	float mass;

	float lifetime, lifetimer;

	inline void update(float& _timeDelta)
	{
		acceleration = force / mass;			// F = ma <=> a = F/m
		speed += acceleration * _timeDelta;		// v = v + dv avec dv = a * dt
		position += speed * _timeDelta;			// p = p + dp avec dp = v * dt
	}
};

#endif