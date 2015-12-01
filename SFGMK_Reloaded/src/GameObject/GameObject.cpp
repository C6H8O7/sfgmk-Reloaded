GameObject::GameObject()
	: name("GameObject"), transformPtr(&transform)
{

}

GameObject::~GameObject()
{
	m_Components.deleteAndClear();
}

void GameObject::update(SFMLCanvas * _canvas)
{
	for (unsigned int i = 0; i < m_Components.getElementNumber(); i++)
		m_Components[i]->OnComponentUpdate(_canvas);
}

void GameObject::draw(SFMLCanvas* _canvas)
{
	for (unsigned int i = 0; i < m_Components.getElementNumber(); i++)
		m_Components[i]->OnDraw(_canvas);
}

void GameObject::OnUpdate(SFMLCanvas * _canvas)
{

}

void GameObject::OnDraw(SFMLCanvas* _canvas)
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
	GameObject* selectedGameObject = MyGUI::GetGUI()->selectedGameObject;

	if (_value == true && selectedGameObject)
		selectedGameObject->showComponents(false);

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
		m_Components[i]->OnPropertiesUpdate();
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