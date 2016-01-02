GameObject::GameObject(r_bool _createDefault)
	: name("GameObject"), transformPtr(&transform), treeID(0)
{
	if (_createDefault)
	{
		addComponent(new ComponentGameObject(this));
		addComponent(new ComponentTransform(this));
	}
}

GameObject::~GameObject()
{
	for (r_uint32 i = 0; i < m_Components.size(); i++)
		delete m_Components[i];
}

r_void GameObject::update(SFMLCanvas * _canvas)
{
	for (r_uint32 i = 0; i < m_Components.getElementNumber(); i++)
		m_Components[i]->OnComponentUpdate(_canvas);
}

r_void GameObject::draw(SFMLCanvas* _canvas)
{
	for (r_uint32 i = 0; i < m_Components.getElementNumber(); i++)
		m_Components[i]->OnDraw(_canvas);
}

r_void GameObject::addComponent(GameObjectComponent* _component)
{
	m_Components.push_back(_component);
}

r_void GameObject::removeComponent(GameObjectComponent* _component)
{
	m_Components.removeElement(_component);
	delete _component;
}

gmk::vector<GameObjectComponent*>& GameObject::getComponents()
{
	return m_Components;
}

#ifdef SFGMKR_EDITOR
r_void GameObject::showComponents(r_bool _value)
{
	if (_value == true)
	{
		MyGUI* gui = MyGUI::GetGUI();

		gui->selectedGameObjectComponent = 0;
		gui->Empty_PropertyGrid();
	}

	for (r_uint32 i = 0; i < m_Components.getElementNumber(); i++)
	{
		GameObjectComponent* component = m_Components[i];

		if (_value == true)
			component->OnPropertiesApparition();
		else
			component->OnPropertiesDisapparition();
	}
}

r_void GameObject::updateComponents()
{
	for (r_uint32 i = 0; i < m_Components.getElementNumber(); i++)
		m_Components[i]->OnPropertiesUpdate();
}

r_void GameObject::AddAsComponent(GameObject* _object, r_string _componentPath)
{
	_componentPath = SFMLCanvas::project->createAssetsPath(_componentPath);

	if (_componentPath.find(".png") != r_string::npos)
	{
		ComponentSprite* sprite = new ComponentSprite(_object);

		sprite->m_Path = _componentPath;
		sprite->m_PathChanged = true;

		sprite->OnMembersUpdate();

		_object->addComponent(sprite);

		_object->showComponents(true);
	}

	else if (_componentPath.find(".lua") != r_string::npos)
	{
		ComponentScript* script = new ComponentScript(_object);

		script->m_Path = _componentPath;
		script->m_PathChanged = true;

		script->OnMembersUpdate();

		_object->addComponent(script);

		_object->showComponents(true);
	}

	else if (_componentPath.find(".tmx") != r_string::npos)
	{
		ComponentTiledMap* map = new ComponentTiledMap(_object);

		map->m_Path = _componentPath;
		map->m_PathChanged = true;

		map->OnMembersUpdate();

		_object->addComponent(map);

		_object->showComponents(true);
	}
}
#endif