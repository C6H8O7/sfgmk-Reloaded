#ifndef SFGMKR_COMPONENTPOSTSHADER_HPP
#define SFGMKR_COMPONENTPOSTSHADER_HPP

#include "stdafx.h"

class ComponentPostShader : public GameObjectComponent
{
	friend class GameObject;

public:

	ComponentPostShader(GameObject* _parent);
	~ComponentPostShader();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

	virtual r_void OnMembersUpdate();

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	sf::Shader m_shader;
	sf::Shader::Type m_shaderType = sf::Shader::Fragment;

	r_string m_Path;
	r_bool m_PathChanged;

	r_bool m_loaded = false;
};

#endif