GameObject::GameObject()
	: name("GameObject")
{

}

GameObject::~GameObject()
{
	m_Components.deleteAndClear();
}

void GameObject::update()
{
	for (unsigned int i = 0; i < m_Components.getElementNumber(); i++)
		m_Components[i]->OnComponentUpdate();
}

void GameObject::draw(sf::RenderWindow* _render)
{
	for (unsigned int i = 0; i < m_Components.getElementNumber(); i++)
		m_Components[i]->OnDraw(_render);
}

void GameObject::OnUpdate()
{

}

void GameObject::OnDraw(sf::RenderWindow* _render)
{

}

void GameObject::addComponent(GameObjectComponent* _component)
{
	m_Components.push_back(_component);

#ifdef SFGMKR_EDITOR
	showComponents(false);
	showComponents(true);
#endif
}

void GameObject::removeComponent(GameObjectComponent* _component)
{
	m_Components.removeElement(_component);
	delete _component;

#ifdef SFGMKR_EDITOR
	showComponents(false);
	showComponents(true);
#endif
}

sfgmk::vector<GameObjectComponent*>& GameObject::getComponents()
{
	return m_Components;
}

void GameObject::showComponents(bool _value)
{
#ifdef SFGMKR_EDITOR
	for (unsigned int i = 0; i < m_Components.getElementNumber(); i++)
	{
		GameObjectComponent* component = m_Components[i];

		if (_value == true)
			component->OnPropertiesApparition();
		else
			component->OnPropertiesDisapparition();
	}
#endif
}

void GameObject::updateComponents()
{
#ifdef SFGMKR_EDITOR
	for (unsigned int i = 0; i < m_Components.getElementNumber(); i++)
	{
		GameObjectComponent* component = m_Components[i];

		component->OnPropertiesUpdate();
	}
#endif
}