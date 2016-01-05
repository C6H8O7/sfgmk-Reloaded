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

GameObjectComponent* GameObject::getComponent(r_string _name)
{
	for (r_uint32 i = 0; i < m_Components.size(); i++)
	{
		if (_name == m_Components[i]->type_name)
			return m_Components[i];
	}
	
	return 0;
}

gmk::vector<GameObjectComponent*> GameObject::getComponents(r_string _name)
{
	gmk::vector<GameObjectComponent*> result;

	for (r_uint32 i = 0; i < m_Components.size(); i++)
	{
		if (_name == m_Components[i]->type_name)
			result.push_back(m_Components[i]);
	}

	return result;
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

	else if (_componentPath.find(".map") != r_string::npos)
	{
		ComponentPathfindingMap* map = new ComponentPathfindingMap(_object);

		map->m_Path = _componentPath;
		map->m_PathChanged = true;

		map->OnMembersUpdate();

		_object->addComponent(map);

		_object->showComponents(true);
	}
}
#endif

r_void GameObject::onPhysicEnter()
{
	for (r_uint32 i = 0; i < m_Scripts.size(); i++)
		m_Scripts[i]->OnPhysicEnter();
}

r_void GameObject::onPhysicCollision(GameObject* _object)
{
	for (r_uint32 i = 0; i < m_Scripts.size(); i++)
		m_Scripts[i]->OnPhysicCollision(_object);
}

r_void GameObject::onPhysicExit()
{
	for (r_uint32 i = 0; i < m_Scripts.size(); i++)
		m_Scripts[i]->OnPhysicExit();
}

r_void GameObject::registerScript(ComponentScript* _component)
{
	m_Scripts.push_back(_component);
}

r_void GameObject::unregisterScript(ComponentScript* _component)
{
	m_Scripts.removeElement(_component);
}

sf::Transform GameObject::getTransform()
{
	sf::Transform result;

	result.translate(transform.position);
	result.scale(transform.scale);
	result.rotate(transform.rotation);

	return result;
}

r_vector2f GameObject::getCenter()
{
	r_vector2f center = transform.position;

	if (ComponentSprite* sprite = (ComponentSprite*)getComponent("Sprite"))
	{
		sf::FloatRect rect = sprite->getSprite()->getGlobalBounds();

		center.x = rect.left + rect.width / 2.0f;
		center.y = rect.top + rect.height / 2.0f;
	}

	return center;
}