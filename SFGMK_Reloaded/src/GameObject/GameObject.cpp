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

#ifdef SFGMKR_EDITOR
void GameObject::showComponents(bool _value)
{
	for (unsigned int i = 0; i < m_Components.getElementNumber(); i++)
	{
		GameObjectComponent* component = m_Components[i];

		if (_value == true)
			component->OnPropertiesApparition();
		else
			component->OnPropertiesDisapparition();
	}
}

void GameObject::updateComponents()
{
	for (unsigned int i = 0; i < m_Components.getElementNumber(); i++)
	{
		GameObjectComponent* component = m_Components[i];

		component->OnPropertiesUpdate();
	}
}

void GameObject::AddAsComponent(GameObject* _object, std::string _componentPath)
{
	if (!_object)
		return;

	_componentPath = Scene::GetRelativePath(_componentPath);

	if (_componentPath.find(".png") != std::string::npos)
	{
		ComponentSprite* sprite = new ComponentSprite(_object);

		sprite->m_Path = _componentPath;
		sprite->m_PathChanged = true;

		_object->addComponent(sprite);
	}

	else if (_componentPath.find(".lua") != std::string::npos)
	{
		ComponentScript* script = new ComponentScript(_object);

		script->m_Path = _componentPath;
		script->m_PathChanged = true;

		_object->addComponent(script);
	}
}
#endif