#include "ParticleSystem.hpp"
ParticleSystem::ParticleSystem(unsigned int _count)
	: m_Vertices(sf::Points, _count), m_Particles(_count)
{
	for (unsigned int i = 0; i < m_Particles.size(); i++)
	{
		resetParticle(m_Particles[i]);
	}
}

void ParticleSystem::setEmitter(sf::Vector2f _emitter)
{
	m_Emitter = _emitter;
}

void ParticleSystem::update(float _timeDelta)
{
	sf::Vector2f null(0.0f, 0.0f);
	sf::Vector2f gravity(0.0f, 9.81f * 10.0f);

	sf::Color color1 = sf::Color::Cyan;
	sf::Color color2 = sf::Color::White;

	int max = (int)m_Particles.size();

	for (int i = 0; i < max; i++)
	{
		Particle& p = m_Particles[i];

		p.lifetimer += _timeDelta;

		p.force = null;
		p.force += gravity;

		p.update(_timeDelta);

		//float t = (p.speed.x * p.speed.x + p.speed.y * p.speed.y) / 20000.0f;
		//t = t > 1.0f ? 1.0f : t;

		float fa = (1.0f - p.lifetimer / p.lifetime);
		fa = fa < 0.0f ? 0.0f : fa;

		//m_Vertices[i].color.r = t * color2.r + (1 - t) * color1.r;
		//m_Vertices[i].color.g = t * color2.g + (1 - t) * color1.g;
		//m_Vertices[i].color.b = t * color2.b + (1 - t) * color1.b;
		m_Vertices[i].color.a = fa * 255;
		m_Vertices[i].position = p.position;

		if (p.lifetimer >= p.lifetime)
			resetParticle(p);
	}
}

void ParticleSystem::resetParticle(Particle& _particle)
{
	float angle = (rand() % 9000) / 100.0f + 45;
	angle *= -1;
	angle = angle * 3.14f / 180.0f;

	sf::Vector2f speed(cosf(angle), sinf(angle));
	speed *= 100.0f;

	_particle.lifetime = (float)(rand()%2000 + 1000) / 1000.0f;
	_particle.lifetimer = 0.0f;

	_particle.speed = speed;

	_particle.position = m_Emitter;
}

void ParticleSystem::draw(SFMLCanvas* _canvas)
{
	sf::RenderStates states;

	states.texture = 0;

	_canvas->draw(m_Vertices, states);
}