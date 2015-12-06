ComponentParticleSystem::ComponentParticleSystem(GameObject * _parent)
	: GameObjectComponent("Particle System", _parent), m_System(50000)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentParticleSystem::~ComponentParticleSystem()
{

}

void ComponentParticleSystem::OnUpdate(SFMLCanvas * _canvas)
{
	if (_canvas->isPlaying)
	{
		gmk::TimeManager* timemanager = gmk::TimeManager::GetSingleton();

		sf::Clock clock;
		clock.restart();

		m_System.update(timemanager->deltaTime);

		m_System.setEmitter(parent->transform.position);
	}
}

void ComponentParticleSystem::OnDraw(SFMLCanvas * _canvas)
{
	if (_canvas->isPlaying)
	{
		sf::Clock clock;
		clock.restart();

		m_System.draw(_canvas);
	}
}

void ComponentParticleSystem::OnMembersUpdate()
{

}

#ifdef SFGMKR_EDITOR
void ComponentParticleSystem::OnRegistration()
{
	beginRegister();

	endRegister();
}
#endif

void ComponentParticleSystem::OnXMLSave(tinyxml2::XMLElement * _element)
{

}

void ComponentParticleSystem::OnXMLLoad(tinyxml2::XMLElement * _element)
{

}