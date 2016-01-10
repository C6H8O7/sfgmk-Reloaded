ComponentScript::ComponentScript(GameObject * _parent)
	: GameObjectComponent("Script", _parent), m_Lua(_parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	parent->registerScript(this);
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
			m_Lua.loadFile(gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path));

			m_Lua.onStart();
		}
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentScript::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);

	endRegister();
}
#endif

r_void ComponentScript::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("path", m_Path.c_str());
}

r_void ComponentScript::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_Path = _element->Attribute("path");
	m_PathChanged = true;
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