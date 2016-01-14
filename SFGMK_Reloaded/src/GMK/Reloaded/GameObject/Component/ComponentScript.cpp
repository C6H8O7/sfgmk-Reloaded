ComponentScript::ComponentScript(GameObject * _parent)
	: GameObjectComponent("Script", _parent), m_Lua(_parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	parent->registerScript(this);

	m_PathChanged = false;
	m_VariablesChanged = false;
}

ComponentScript::~ComponentScript()
{
	parent->unregisterScript(this);
}

r_void ComponentScript::OnUpdate(SFMLCanvas * _canvas)
{
	if (!SFMLCanvas::isPlaying)
		return;

	m_Lua.onUpdate();
}

r_void ComponentScript::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentScript::OnMembersUpdate()
{
	if (m_PathChanged)
	{
		m_PathChanged = false;

		if (m_Path.find(".lua") != r_string::npos)
		{
			r_string luaFile = gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path);

			m_Lua.loadFile(luaFile);

			if (!m_VariablesChanged)
			{
				m_Lua.emptyVariables();
				m_Lua.parseVariables(luaFile);
			}

			m_Lua.onVariablesRefresh();

#ifdef SFGMKR_EDITOR
			RefreshScript();
#endif

			m_Lua.onStart();
		}
	}

	if (m_VariablesChanged)
	{
		m_VariablesChanged = false;

		m_Lua.onVariablesRefresh();
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentScript::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);

	gmk::vector<gmk::sLUA_VARIABLE*>* variables = m_Lua.getVariables();

	for (r_uint32 i = 0; i < variables->size(); i++)
	{
		gmk::sLUA_VARIABLE* variable = (*variables)[i];
		registerProperty((GameObjectComponent::ePROPERTY_TYPE)variable->type, variable->name, variable->data, &m_VariablesChanged);
	}

	registerProperty(ePROPERTY_TYPE::TYPE_BUTTON, "Reload Script", 0, 0, false, (wxObjectEventFunction)&ComponentScript::ReloadScript);

	endRegister();
}

r_void ComponentScript::RefreshScript()
{
	parent->showComponents(false);

	unregisterProperties();
	OnRegistration();

	parent->showComponents(true);
}

r_void ComponentScript::ReloadScript(wxEvent& _event)
{
	m_PathChanged = true;
	OnMembersUpdate();

	RefreshScript();
}
#endif

r_void ComponentScript::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("path", m_Path.c_str());

	gmk::vector<gmk::sLUA_VARIABLE*>* variables = m_Lua.getVariables();
	for (r_uint32 i = 0; i < variables->size(); i++)
	{
		gmk::sLUA_VARIABLE* variable = (*variables)[i];

		tinyxml2::XMLElement* elemVariable = _element->GetDocument()->NewElement("Variable");

		elemVariable->SetAttribute("type", variable->type);
		elemVariable->SetAttribute("name", variable->name.c_str());

		switch (variable->type)
		{
			case gmk::eLUA_VARIABLE_TYPE::LUA_STRING:
				elemVariable->SetAttribute("value", (*(r_string*)variable->data).c_str());
				break;

			case gmk::eLUA_VARIABLE_TYPE::LUA_INT:
				elemVariable->SetAttribute("value", *(r_int32*)variable->data);
				break;

			case gmk::eLUA_VARIABLE_TYPE::LUA_FLOAT:
				elemVariable->SetAttribute("value", *(r_float*)variable->data);
				break;
		}

		_element->LinkEndChild(elemVariable);
	}
}

r_void ComponentScript::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Path = _element->Attribute("path");
	m_PathChanged = true;

	gmk::vector<gmk::sLUA_VARIABLE*>* variables = m_Lua.getVariables();
	tinyxml2::XMLElement* elemVariable = _element->FirstChildElement("Variable");
	while (elemVariable)
	{
		gmk::sLUA_VARIABLE* variable = new gmk::sLUA_VARIABLE();

		variable->type = (gmk::eLUA_VARIABLE_TYPE)elemVariable->IntAttribute("type");
		variable->name = elemVariable->Attribute("name");

		switch (variable->type)
		{
			case gmk::eLUA_VARIABLE_TYPE::LUA_STRING:
				variable->data = new r_string(elemVariable->Attribute("value"));
				variable->function = &gmk::SetGlobal<r_string>;
				break;

			case gmk::eLUA_VARIABLE_TYPE::LUA_INT:
				variable->data = new r_int32(elemVariable->IntAttribute("value"));
				variable->function = &gmk::SetGlobal<r_int32>;
				break;

			case gmk::eLUA_VARIABLE_TYPE::LUA_FLOAT:
				variable->data = new r_float(elemVariable->FloatAttribute("value"));
				variable->function = &gmk::SetGlobal<r_float>;
				break;
		}

		variables->push_back(variable);

		elemVariable = elemVariable->NextSiblingElement("Variable");
	}
	m_VariablesChanged = true;
}

r_void ComponentScript::OnPhysicEnter()
{
	m_Lua.onPhysicEnter();
}

r_void ComponentScript::OnPhysicCollision(GameObject* _object)
{
	m_Lua.onPhysicCollision(_object);
}

r_void ComponentScript::OnPhysicExit()
{
	m_Lua.onPhysicExit();
}

r_void ComponentScript::onScriptLoad()
{

}