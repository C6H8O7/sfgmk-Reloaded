#ifndef SFGMKR_PARTICLESYSTEM_HPP
#define SFGMKR_PARTICLESYSTEM_HPP

class SFMLCanvas;

class ParticleSystem
{
public:

	ParticleSystem(unsigned int _count);
	~ParticleSystem();

	void setEmitter(sf::Vector2f _emitter);

	void update(float _timeDelta);

	void draw(SFMLCanvas* _canvas);

private:

	std::vector<Particle> m_Particles;
	sf::VertexArray m_Vertices;
	sf::Vector2f m_Emitter;

	Particle** m_ParticlesPtr;
	sf::Vertex** m_VerticesPtr;
};

#endif