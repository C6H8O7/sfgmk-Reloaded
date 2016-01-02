#ifndef SFGMKR_PARTICLESYSTEM_HPP
#define SFGMKR_PARTICLESYSTEM_HPP

class SFMLCanvas;

class ParticleSystem
{
public:

	ParticleSystem(r_uint32 _count);
	~ParticleSystem();

	r_void setEmitter(r_vector2f _emitter);

	r_void update(r_float _timeDelta);

	r_void draw(SFMLCanvas* _canvas);

private:

	std::vector<Particle> m_Particles;
	sf::VertexArray m_Vertices;
	r_vector2f m_Emitter;

	Particle** m_ParticlesPtr;
	sf::Vertex** m_VerticesPtr;
};

#endif