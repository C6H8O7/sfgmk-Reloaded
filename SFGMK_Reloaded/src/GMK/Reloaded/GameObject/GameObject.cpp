#include "stdafx.h"

GameObject::GameObject()
	: name("GameObject"), transformPtr(&transform), treeID(0), debugPtr(&debug), ptr(this), soundBufferPtr(0), steeringPtr(0), m_pendingDeletion(false)
{
	addComponent(new ComponentGameObject(this));
	addComponent(new ComponentTransform(this));
}

GameObject::GameObject(r_bool _createDefault)
	: name("GameObject"), transformPtr(&transform), treeID(0), debugPtr(&debug), ptr(this), soundBufferPtr(0), steeringPtr(0), m_pendingDeletion(false)
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
	for (r_uint32 i = 0; i < m_Components.size(); i++)
		m_Components[i]->OnComponentUpdate(_canvas);

	if (m_pendingDeletion)
		SFMLCanvas::project->getCurrentScene()->removeGameObject(this);
}

r_void GameObject::draw(SFMLCanvas* _canvas)
{
	for (r_uint32 i = 0; i < m_Components.size(); i++)
		m_Components[i]->OnDraw(_canvas);
}

r_void GameObject::destroy()
{
	m_pendingDeletion = true;
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

	for (r_uint32 i = 0; i < m_Components.size(); i++)
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
	for (r_uint32 i = 0; i < m_Components.size(); i++)
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

		map->OnMembersUpdate();

		_object->addComponent(map);

		_object->showComponents(true);
	}

	else if (_componentPath.find(".frag") != r_string::npos)
	{
		ComponentShader* NewShader = new ComponentShader(_object);

		NewShader->m_Path = _componentPath;
		NewShader->m_PathChanged = true;

		NewShader->OnMembersUpdate();

		_object->addComponent(NewShader);

		_object->showComponents(true);
	}

	else if (_componentPath.find(".ttf") != r_string::npos ||
		_componentPath.find(".otf") != r_string::npos)
	{
		ComponentText* text = new ComponentText(_object);

		text->m_FontPath = _componentPath;
		text->m_FontPathChanged = true;

		text->OnMembersUpdate();

		_object->addComponent(text);

		_object->showComponents(true);
	}

	else if( _componentPath.find(".prefab") != r_string::npos )
	{
		_object->getComponents().deleteAndClear();

		r_string PrefabName = _componentPath;
		r_uint32 iIndex(0U);

		PrefabName = PrefabName.substr((iIndex = PrefabName.find_last_of('/') + 1), PrefabName.find_last_of('.') - iIndex);
		gmk::Factory::getSingleton()->instantiate(PrefabName, _object);
	}
}
#endif

r_void GameObject::onPhysicEnter()
{
	for (r_uint32 i = 0; i < m_PhysicFuncs.size(); i++)
		m_PhysicFuncs[i]->enter(m_PhysicFuncs[i]->object);

	for (r_uint32 i = 0; i < m_Scripts.size(); i++)
		m_Scripts[i]->OnPhysicEnter();
}

r_void GameObject::onPhysicCollisionEnter(GameObject* _object)
{
	for (r_uint32 i = 0; i < m_Scripts.size(); i++)
		m_Scripts[i]->OnPhysicCollisionEnter(_object);
}

r_void GameObject::onPhysicCollision(GameObject* _object)
{
	for (r_uint32 i = 0; i < m_PhysicFuncs.size(); i++)
		m_PhysicFuncs[i]->collision(m_PhysicFuncs[i]->object, _object);

	for (r_uint32 i = 0; i < m_Scripts.size(); i++)
		m_Scripts[i]->OnPhysicCollision(_object);
}

r_void GameObject::onPhysicExit()
{
	for (r_uint32 i = 0; i < m_PhysicFuncs.size(); i++)
		m_PhysicFuncs[i]->exit(m_PhysicFuncs[i]->object);

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
	r_vector2f center = transform.position + transform.scale * 0.5f;

	if (ComponentSprite* sprite = (ComponentSprite*)getComponent("Sprite"))
	{
		sf::FloatRect rect = sprite->getSprite()->getGlobalBounds();

		center.x = rect.left + rect.width * 0.5f;
		center.y = rect.top + rect.height * 0.5f;
	}

	return center;
}

r_void GameObject::addPhysicFuncs(sGAMEOBJECT_PHYSICFUNCS* _funcs)
{
	m_PhysicFuncs.push_back(_funcs);
}

r_void GameObject::removePhysicFuncs(sGAMEOBJECT_PHYSICFUNCS* _funcs)
{
	m_PhysicFuncs.removeElement(_funcs);
}

r_void GameObject::computePathfinding(r_vector2f _begin, r_vector2f _end, r_bool _smooth, r_float _caseSize)
{
	for (r_uint32 i = 0; i < pathfindingAgents.size(); i++)
		pathfindingAgents[i]->computePathfinding(_begin, _end, _smooth, _caseSize);
}