#include "stdafx.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	for (r_uint32 i = 0; i < m_Components.size(); i++)
		delete m_Components[i];

	for (r_uint32 i = 0; i < m_children.size(); i++)
		m_children[i]->setParent(m_parent);

	setParent(0);
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

	gmk::vector<GameObject*> children = m_children;
	for (r_uint32 i = 0; i < children.size(); i++)
		children[i]->draw(_canvas);
}

r_void GameObject::destroy()
{
	m_pendingDeletion = true;
}

r_void GameObject::hardDestroy()
{
	if (networkID)
		gmk::net::NetworkManager::GetInstance()->sendState(this, gmk::net::PacketHandling::GameObjectStateState::Dead);

	SFMLCanvas::project->getCurrentScene()->removeGameObject(this);
}

r_void GameObject::addDefaultComponents()
{
	addComponent(new ComponentGameObject(this));
	addComponent(new ComponentTransform(this));
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

gmk::vector<ComponentScript*>& GameObject::getScripts()
{
	return m_Scripts;
}

gmk::LuaScript GameObject::getScriptByName(r_string _name)
{
	for (r_uint32 i = 0; i < m_Scripts.size(); i++)
		if (_name == m_Scripts[i]->getScriptName())
			return gmk::LuaScript(m_Scripts[i]->getScript());

	return gmk::LuaScript(0);
}

r_vector2f GameObject::getCenter()
{
	r_vector2f center = transform.getPosition() + transform.getScale() * 0.5f;

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

r_void GameObject::setParent(GameObject* _gameObject)
{
	if (m_parent)
		m_parent->getChildren().removeElement(this);

	m_parent = _gameObject;

	if (m_parent)
		m_parent->getChildren().push_back(this);
}

GameObject*& GameObject::getParent()
{
	return m_parent;
}

gmk::vector<GameObject*>& GameObject::getChildren()
{
	return m_children;
}

r_void GameObject::OnXMLSave(tinyxml2::XMLElement* _element)
{
	tinyxml2::XMLElement* gameobject_elem = _element->GetDocument()->NewElement("GameObject");

	_element->LinkEndChild(gameobject_elem);

	for (r_uint32 i = 0; i < m_Components.size(); i++)
	{
		GameObjectComponent* component = m_Components[i];

		tinyxml2::XMLElement* component_elem = gameobject_elem->GetDocument()->NewElement("Component");

		gameobject_elem->LinkEndChild(component_elem);

		component_elem->SetAttribute("type", component->type_name.c_str());

		component->OnXMLSave(component_elem);
	}

	for (r_uint32 i = 0; i < m_children.size(); i++)
	{
		GameObject* child = m_children[i];

		child->OnXMLSave(gameobject_elem);
	}
}

r_void GameObject::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	tinyxml2::XMLElement* component_elem = _element->FirstChildElement("Component");

	while (component_elem)
	{
		GameObjectComponent* component = 0;
		r_string type = component_elem->Attribute("type");

		component = ComponentsBank::GetSingleton()->createComponent(type, this);

		if (component)
		{
			component->OnXMLLoad(component_elem);

			component->OnMembersUpdate();

			this->addComponent(component);
		}

		component_elem = component_elem->NextSiblingElement("Component");
	}

	SFMLCanvas::project->getCurrentScene()->addGameObject(this);

	tinyxml2::XMLElement* gameobject_elem = _element->FirstChildElement("GameObject");

	while (gameobject_elem)
	{
		GameObject* gameobject = new GameObject();
		gameobject->setParent(this);

		gameobject->OnXMLLoad(gameobject_elem);

		gameobject_elem = gameobject_elem->NextSiblingElement("GameObject");
	}
}