#ifndef SFGMKR_PARTICLESYSTEM_HPP
#define SFGMKR_PARTICLESYSTEM_HPP

class SFMLCanvas;

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

	ParticleSystem(unsigned int _count);

	void setEmitter(sf::Vector2f _emitter);

	void update(SFMLCanvas* _canvas, float _timeDelta);

private:

	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;

	std::vector<Particle> m_Particles;
	sf::VertexArray m_Vertices;
	sf::Vector2f m_Emitter;
};

#endif