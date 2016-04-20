#include "stdafx.h"

ComponentPostShader::ComponentPostShader(GameObject* _parent)
	: GameObjectComponent("PostShader", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentPostShader::~ComponentPostShader()
{

}

r_void ComponentPostShader::OnUpdate(SFMLCanvas * _canvas)
{

}

r_void ComponentPostShader::OnDraw(SFMLCanvas* _canvas)
{
	if (m_loaded)
		gmk::RenderManager::GetInstance()->registerOneShotPostShader(&m_shader);
}

r_void ComponentPostShader::OnMembersUpdate()
{
	if (m_PathChanged)
	{
		m_PathChanged = false;

		if (m_Path.size())
			if (m_loaded = m_shader.loadFromFile(gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path), m_shaderType))
				m_shader.setUniform("_currentTexture", sf::Shader::CurrentTexture);
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentPostShader::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);

	GameObjectComponent::ComponentProperty* propertyType = registerProperty(ePROPERTY_TYPE::TYPE_ENUM, "Type", &m_shaderType);
	propertyType->wxChoices.Add("Fragment", sf::Shader::Fragment);
	propertyType->wxChoices.Add("Vertex", sf::Shader::Vertex);

	endRegister();
}
#endif

r_void ComponentPostShader::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("path", m_Path.c_str());
	_element->SetAttribute("shadertype", m_shaderType);
}

r_void ComponentPostShader::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_shaderType = (sf::Shader::Type)_element->IntAttribute("shadertype");

	m_Path = _element->Attribute("path");
	m_PathChanged = true;
}