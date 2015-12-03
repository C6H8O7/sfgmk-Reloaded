#include "ParticleSystem.hpp"
ParticleSystem::ParticleSystem(unsigned int _count)
	: m_Vertices(sf::Points, _count), m_Particles(_count)
{
	int d = (int)sqrtf(_count);

	int i = 0;
	for (int x = 0; x < d; x++)
	{
		for (int y = 0; y < d; y++)
		{
			m_Vertices[i].color = sf::Color::White;
			m_Particles[i++].position = sf::Vector2f(x, y);
		}
	}
}

void ParticleSystem::setEmitter(sf::Vector2f _emitter)
{
	m_Emitter = _emitter;
}

void ParticleSystem::update(SFMLCanvas* _canvas, float _timeDelta)
{
	sfgmk::Mouse& mouse = _canvas->getInputManager()->getMouse();

	bool mouseDown = false;
	sf::Vector2f mouseForce;
	sf::Vector2f mousePos = mouse.getWorldPosition();
	sf::Vector2f null(0.0f, 0.0f);

	if (mouse.getButtonState(sf::Mouse::Left) == KEY_DOWN)
		mouseDown = true;

	for (unsigned int i = 0; i < m_Particles.size(); i++)
	{
		Particle& p = m_Particles[i];

		if (mouseDown)
		{
			mouseForce = (mouse.getWorldPosition() - p.position);
			p.force += mouseForce;
		}

		p.force += -p.speed;

		p.update(_timeDelta);

		p.force = null;

		m_Vertices[i].position = p.position;
	}
}

void ParticleSystem::draw(sf::RenderTarget & _target, sf::RenderStates _states) const
{
	// on applique la transformation
	_states.transform *= getTransform();

	// nos particules n'utilisent pas de texture
	_states.texture = 0;

	// on dessine enfin le vertex array
	_target.draw(m_Vertices, _states);
}