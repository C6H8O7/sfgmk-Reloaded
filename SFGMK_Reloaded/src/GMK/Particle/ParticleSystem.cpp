#include "ParticleSystem.hpp"
ParticleSystem::ParticleSystem(unsigned int _count)
	: m_Vertices(sf::Points, _count), m_Particles(_count)
{
	m_ParticlesPtr = new Particle*[_count];
	m_VerticesPtr = new sf::Vertex*[_count];

	for (unsigned int i = 0; i < m_Particles.size(); i++)
	{
		m_ParticlesPtr[i] = &m_Particles[i];
		m_VerticesPtr[i] = &m_Vertices[i];
		resetParticle(m_Particles[i]);
	}
}

void ParticleSystem::setEmitter(sf::Vector2f _emitter)
{
	m_Emitter = _emitter;
}

void ParticleSystem::update(float _timeDelta)
{
	sf::Vector2f gravity(0.0f, 9.81f * 10.0f);

	sf::Vector2f constantForce = gravity;

	int max = (int)m_Particles.size();

	Particle** pptr = m_ParticlesPtr;
	sf::Vertex** vptr = m_VerticesPtr;

	Particle *p = 0;
	sf::Vertex *v = 0;

	float fa;

	int i = max;

	while(i--)
	{
		p = *pptr++;
		v = *vptr++;

		p->lifetimer += _timeDelta;

		p->force = constantForce;

		/*if (p->position.x < 0.0f)
			p->speed.x += (float)(rand() % 50 + 50);
		else if (p->position.x > 1280.0f)
			p->speed.x -= (float)(rand() % 50 + 50);
		else if (p->position.y < 0.0f)
			p->speed.y += (float)(rand() % 50 + 50);
		else if (p->position.y > 720.0f)
			p->speed.y -= (float)(rand() % 50 + 50);*/

		p->update(_timeDelta);

		fa = (1.0f - p->lifetimer * p->lifetimeinv);
		fa = fa < 0.0f ? 0.0f : fa;

		v->color.a = (uint8_t)(fa * 255.0f);
		v->position = p->position;

		if (p->lifetimer >= p->lifetime)
			resetParticle(*p);
	}
}

void ParticleSystem::resetParticle(Particle& _particle)
{
	float angle = (rand() % 3600) / 10.0f;
	angle = angle * 3.14f / 180.0f;

	sf::Vector2f speed(cosf(angle), sinf(angle));
	speed *= (float)(rand()%100 + 100);

	_particle.lifetime = (float)(rand()%50000 + 50000) / 10000.0f;
	_particle.lifetimeinv = 1.0f / _particle.lifetime;
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