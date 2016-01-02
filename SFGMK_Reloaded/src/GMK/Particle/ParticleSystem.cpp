ParticleSystem::ParticleSystem(r_uint32 _count)
	: m_Vertices(sf::Points, _count), m_Particles(_count)
{
	m_ParticlesPtr = new Particle*[_count];
	m_VerticesPtr = new sf::Vertex*[_count];

	for (r_uint32 i = 0; i < m_Particles.size(); i++)
	{
		m_ParticlesPtr[i] = &m_Particles[i];
		m_VerticesPtr[i] = &m_Vertices[i];
		m_Particles[i].reset(m_Emitter);
	}
}

ParticleSystem::~ParticleSystem()
{
	delete m_ParticlesPtr;
	delete m_VerticesPtr;
}

r_void ParticleSystem::setEmitter(r_vector2f _emitter)
{
	m_Emitter = _emitter;
}

r_void ParticleSystem::update(r_float _timeDelta)
{
	r_vector2f gravity(0.0f, 9.81f * 10.0f);

	r_vector2f constantForce = gravity;

	Particle** pptr = m_ParticlesPtr;
	sf::Vertex** vptr = m_VerticesPtr;

	Particle *p = 0;
	sf::Vertex *v = 0;

	r_int32 max = (r_int32)m_Particles.size();

	for (r_int32 i = 0; i < max; i++)
	{
		p = *pptr++;
		v = *vptr++;

		p->lifetimer += _timeDelta;

		p->force = constantForce;

		p->update(_timeDelta);

		r_float fa = (1.0f - p->lifetimer * p->lifetimeinv);
		fa = fa < 0.0f ? 0.0f : fa;

		v->color.a = (uint8_t)(fa * 255.0f);
		v->position = p->position;

		if (p->lifetimer >= p->lifetime)
			p->reset(m_Emitter);
	}
}

r_void ParticleSystem::draw(SFMLCanvas* _canvas)
{
	_canvas->draw(m_Vertices);
}