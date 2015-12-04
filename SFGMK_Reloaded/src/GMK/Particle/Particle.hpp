#ifndef SFGMKR_PARTICLE_HPP
#define SFGMKR_PARTICLE_HPP

class Particle
{
public:

	Particle(sf::Vector2f& _position = sf::Vector2f(), float _mass = 1.0f);
	~Particle();

	sf::Vector2f position;
	sf::Vector2f speed;
	sf::Vector2f force;

	float mass;

	float lifetime, lifetimeinv, lifetimer;

	inline void update(float& _timeDelta)
	{
												// F = ma <=> a = F/m
		speed += force / mass * _timeDelta;		// v = v + dv avec dv = a * dt
		position += speed * _timeDelta;			// p = p + dp avec dp = v * dt
	}
};

#endif