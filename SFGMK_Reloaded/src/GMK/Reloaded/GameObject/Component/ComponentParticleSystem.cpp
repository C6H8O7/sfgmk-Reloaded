ComponentParticleSystem::ComponentParticleSystem(GameObject * _parent)
	: GameObjectComponent("ParticleSystem", _parent), m_System(300000)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentParticleSystem::~ComponentParticleSystem()
{

}

r_void ComponentParticleSystem::OnUpdate(SFMLCanvas * _canvas)
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

r_void ComponentParticleSystem::OnDraw(SFMLCanvas * _canvas)
{
	if (_canvas->isPlaying)
	{
		sf::Clock clock;
		clock.restart();

		m_System.draw(_canvas);
	}
}

r_void ComponentParticleSystem::OnMembersUpdate()
{

}

#ifdef SFGMKR_EDITOR
r_void ComponentParticleSystem::OnRegistration()
{
	beginRegister();

	endRegister();
}
#endif

r_void ComponentParticleSystem::OnXMLSave(tinyxml2::XMLElement * _element)
{

}

r_void ComponentParticleSystem::OnXMLLoad(tinyxml2::XMLElement * _element)
{

}