#include "stdafx.h"

void(*ComponentShader::setParameterFunctionsPtr[eSHADER_PROPERTY_TYPE_NUMBER])(sf::Shader&, const r_string&, void*, ComponentShader*) = { &ComponentShader::setShaderParameterCurrentTexture,
																																			&ComponentShader::setShaderParameterTexture,
																																			&ComponentShader::setShaderParameterFloat,
																																			&ComponentShader::setShaderParameterMousePosition,
																																			&ComponentShader::setShaderParameterVec2,
																																			&ComponentShader::setShaderParameterVec3,
																																			&ComponentShader::setShaderParameterVec4,
																																			&ComponentShader::setShaderParameterColor };

ComponentShader::ComponentShader(GameObject * _parent)
	: GameObjectComponent("Shader", _parent), m_Path(""), m_PathChanged(false), m_bUpdateEveryFrame(false)
{
}

ComponentShader::~ComponentShader()
{
	releaseShaderVars();
	m_ShaderTextures.clear();
}


r_void ComponentShader::OnUpdate(SFMLCanvas * _canvas)
{
	for( r_uint32 i(0); i < m_ShaderVars.size(); i++ )
	{
		if( m_bUpdateEveryFrame || m_ShaderVars[i]->bChanged )
		{
			m_ShaderVars[i]->bChanged = false;
			setParameterFunctionsPtr[m_ShaderVars[i]->Type](m_Shader, m_ShaderVars[i]->Name, m_ShaderVars[i]->Var, this);
		}
	}
}

r_void ComponentShader::OnMembersUpdate()
{
	for( auto it = m_ShaderTextures.begin(); it != m_ShaderTextures.end(); ++it )
	{
		if( m_ShaderVars[(*it).second.uiVectorIndex]->bChanged )
			(*it).second.Texture.loadFromFile(gmk::AssetsManager::GetSingleton()->getAssetPath((*(r_string*)m_ShaderVars[(*it).second.uiVectorIndex]->Var)));
	}

	if( m_PathChanged )
	{
		m_PathChanged = false;
		releaseShaderVars();
		m_ShaderTextures.clear();

		if( m_Path.size() )
		{
			sf::Uint32 uiVectorIndex(0U);
			r_string Path;

			if( m_Shader.loadFromFile(Path = gmk::AssetsManager::GetSingleton()->getAssetPath(m_Path), sf::Shader::Fragment) )
			{
				//Parse les variables uniform
				FILE* File = NULL;
				r_int8 Buffer[64];

				fopen_s(&File, Path.c_str(), "r");
				if( !File )
				{
					std::cout << "L'asset " << m_Path << " est introuvable." << std::endl;
					return;
				}

				//Tant qu'il y a des lignes dans le fichier
				while( fgets(Buffer, 63, File) )
				{
					//Si la ligne commence par "uniform"
					r_int8 Temp[sizeof("uniform")] = "\0";

					for( r_uint32 i(0); i < sizeof("uniform"); i++ )
						Temp[i] = Buffer[i];
					Temp[sizeof("uniform") - 1] = '\0';

					if( strcmp(Temp, "uniform") == 0 )
					{
						r_string Line(Buffer);
						r_string Type;
						r_string Name;

						Type = Line.substr(sizeof("uniform"), Line.length());
						Type = Type.substr(0, Type.find_first_of(' '));

						Name = Line.substr(sizeof("uniform"), Line.length());
						Name = Name.substr(Name.find_first_of(' ') + 1, Name.length());
						Name = Name.substr(0, Name.find_first_of(" ;"));

						if( Type == "sampler2D" )
						{
							if( Line.find("//CurrentTexture", 0) != std::string::npos )
							{
								stSHADER_VAR* NewVar = new stSHADER_VAR(eSHADER_PROPERTY_TYPE::eCURRENT_TEXTURE, Name, NULL);
								m_ShaderVars.push_back(NewVar);
							}
							else
							{
								stSHADER_VAR* NewVar = new stSHADER_VAR(eSHADER_PROPERTY_TYPE::eTEXTURE, Name, new r_string("NULL"));
								m_ShaderVars.push_back(NewVar);

								m_ShaderTextures.insert(std::pair<r_string, stSHADER_TEXTURE>(Name, stSHADER_TEXTURE(uiVectorIndex, false)));
							}
						}
						else if( Type == "float" )
						{
							stSHADER_VAR* NewVar = new stSHADER_VAR(eSHADER_PROPERTY_TYPE::eFLOAT, Name, (float*)calloc(1, sizeof(float)));
							m_ShaderVars.push_back(NewVar);
						}
						else if( Type == "vec2" )
						{
							if( Line.find("//MousePosition", 0) != std::string::npos )
							{
								stSHADER_VAR* NewVar = new stSHADER_VAR(eSHADER_PROPERTY_TYPE::eMOUSE_POSITION, Name, NULL);
								m_ShaderVars.push_back(NewVar);
							}
							else
							{
								stSHADER_VAR* NewVar = new stSHADER_VAR(eSHADER_PROPERTY_TYPE::eVEC2, Name, (sf::Glsl::Vec2*)calloc(1, sizeof(sf::Glsl::Vec2)));
								m_ShaderVars.push_back(NewVar);
							}
						}
						else if( Type == "vec3" )
						{
							stSHADER_VAR* NewVar = new stSHADER_VAR(eSHADER_PROPERTY_TYPE::eVEC3, Name, (sf::Glsl::Vec3*)calloc(1, sizeof(sf::Glsl::Vec3)));
							m_ShaderVars.push_back(NewVar);
						}
						else if( Type == "vec4" )
						{
							if( Line.find("//Color", 0) != std::string::npos )
							{
								stSHADER_VAR* NewVar = new stSHADER_VAR(eSHADER_PROPERTY_TYPE::eCOLOR, Name, (sf::Color*)calloc(1, sizeof(sf::Color)));
								m_ShaderVars.push_back(NewVar);
							}
							else
							{
								stSHADER_VAR* NewVar = new stSHADER_VAR(eSHADER_PROPERTY_TYPE::eVEC4, Name, (sf::Glsl::Vec4*)calloc(1, sizeof(sf::Glsl::Vec4)));
								m_ShaderVars.push_back(NewVar);
							}
						}

						uiVectorIndex++;
					}
				}
			
				fclose(File);

			#ifdef SFGMKR_EDITOR
				OnRegistration();
			#endif
			}
		}
	}
}

#ifdef SFGMKR_EDITOR
r_void ComponentShader::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Path", &m_Path, &m_PathChanged);
	registerProperty(ePROPERTY_TYPE::TYPE_BOOL, "Update Every frame", &m_bUpdateEveryFrame);

	for( r_uint32 i(0); i < m_ShaderVars.size(); i++ )
	{
		switch( m_ShaderVars[i]->Type )
		{
			case eCURRENT_TEXTURE:
				break;
				
			case eTEXTURE:
				registerProperty(ePROPERTY_TYPE::TYPE_STRING, m_ShaderVars[i]->Name, m_ShaderVars[i]->Var, &m_ShaderVars[m_ShaderTextures[m_ShaderVars[i]->Name].uiVectorIndex]->bChanged);
				break;

			case eFLOAT:
				registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, m_ShaderVars[i]->Name, m_ShaderVars[i]->Var, &m_ShaderVars[i]->bChanged);
				break;

			case eVEC2:
				registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, m_ShaderVars[i]->Name + ".X", &((sf::Glsl::Vec2*)(m_ShaderVars[i]->Var))->x, &m_ShaderVars[i]->bChanged);
				registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, m_ShaderVars[i]->Name + ".Y", &((sf::Glsl::Vec2*)(m_ShaderVars[i]->Var))->y, &m_ShaderVars[i]->bChanged);
				break;

			case eVEC3:
				registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, m_ShaderVars[i]->Name + ".X", &((sf::Glsl::Vec3*)(m_ShaderVars[i]->Var))->x, &m_ShaderVars[i]->bChanged);
				registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, m_ShaderVars[i]->Name + ".Y", &((sf::Glsl::Vec3*)(m_ShaderVars[i]->Var))->y, &m_ShaderVars[i]->bChanged);
				registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, m_ShaderVars[i]->Name + ".Z", &((sf::Glsl::Vec3*)(m_ShaderVars[i]->Var))->z, &m_ShaderVars[i]->bChanged);
				break;

			case eVEC4:
				registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, m_ShaderVars[i]->Name + ".X", &((sf::Glsl::Vec4*)(m_ShaderVars[i]->Var))->x, &m_ShaderVars[i]->bChanged);
				registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, m_ShaderVars[i]->Name + ".Y", &((sf::Glsl::Vec4*)(m_ShaderVars[i]->Var))->y, &m_ShaderVars[i]->bChanged);
				registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, m_ShaderVars[i]->Name + ".Z", &((sf::Glsl::Vec4*)(m_ShaderVars[i]->Var))->z, &m_ShaderVars[i]->bChanged);
				registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, m_ShaderVars[i]->Name + ".W", &((sf::Glsl::Vec4*)(m_ShaderVars[i]->Var))->w, &m_ShaderVars[i]->bChanged);
				break;

			case eCOLOR:
				registerProperty(ePROPERTY_TYPE::TYPE_COLOR, m_ShaderVars[i]->Name, m_ShaderVars[i]->Var, &m_ShaderVars[i]->bChanged);
				break;

			default:
				break;
		}
	}

	endRegister();
}

r_void ComponentShader::OnEditorUpdate()
{
}
#endif

r_void ComponentShader::OnXMLSave(tinyxml2::XMLElement * _element)
{
	_element->SetAttribute("path", m_Path.c_str());
	_element->SetAttribute("update", m_bUpdateEveryFrame);
	
	for( r_uint32 i(0); i < m_ShaderVars.size(); i++ )
	{
		tinyxml2::XMLElement* elemVariable = _element->GetDocument()->NewElement("Variable");

		elemVariable->SetAttribute("type", m_ShaderVars[i]->Type);
		elemVariable->SetAttribute("name", m_ShaderVars[i]->Name.c_str());

		switch( m_ShaderVars[i]->Type )
		{
			case eTEXTURE:
				elemVariable->SetAttribute("value", (*(r_string*)m_ShaderVars[i]->Var).c_str());
				break;

			case eFLOAT:
				elemVariable->SetAttribute("value", *(float*)m_ShaderVars[i]->Var);
				break;

			case eVEC2:
				elemVariable->SetAttribute("valueX", (*(sf::Glsl::Vec2*)m_ShaderVars[i]->Var).x);
				elemVariable->SetAttribute("valueY", (*(sf::Glsl::Vec2*)m_ShaderVars[i]->Var).y);
				break;

			case eVEC3:
				elemVariable->SetAttribute("valueX", (*(sf::Glsl::Vec3*)m_ShaderVars[i]->Var).x);
				elemVariable->SetAttribute("valueY", (*(sf::Glsl::Vec3*)m_ShaderVars[i]->Var).y);
				elemVariable->SetAttribute("valueZ", (*(sf::Glsl::Vec3*)m_ShaderVars[i]->Var).z);
				break;

			case eVEC4:
				elemVariable->SetAttribute("valueX", (*(sf::Glsl::Vec4*)m_ShaderVars[i]->Var).x);
				elemVariable->SetAttribute("valueY", (*(sf::Glsl::Vec4*)m_ShaderVars[i]->Var).y);
				elemVariable->SetAttribute("valueZ", (*(sf::Glsl::Vec4*)m_ShaderVars[i]->Var).z);
				elemVariable->SetAttribute("valueW", (*(sf::Glsl::Vec4*)m_ShaderVars[i]->Var).w);
				break;

			case eCOLOR:
				elemVariable->SetAttribute("valueR", (sf::Uint8)(*(sf::Color*)m_ShaderVars[i]->Var).r);
				elemVariable->SetAttribute("valueG", (sf::Uint8)(*(sf::Color*)m_ShaderVars[i]->Var).g);
				elemVariable->SetAttribute("valueB", (sf::Uint8)(*(sf::Color*)m_ShaderVars[i]->Var).b);
				elemVariable->SetAttribute("valueA", (sf::Uint8)(*(sf::Color*)m_ShaderVars[i]->Var).a);
				break;

			default:
				break;
		}

		_element->LinkEndChild(elemVariable);
	}
}

r_void ComponentShader::OnXMLLoad(tinyxml2::XMLElement * _element)
{
	m_Path = _element->Attribute("path");
	m_PathChanged = true;
	OnMembersUpdate();

	m_bUpdateEveryFrame = _element->BoolAttribute("update");

	r_uint32 uiIndex(0U);
	tinyxml2::XMLElement* elemVariable = _element->FirstChildElement("Variable");
	while( elemVariable )
	{
		m_ShaderVars[uiIndex]->Type = (eSHADER_PROPERTY_TYPE)elemVariable->IntAttribute("type");
		m_ShaderVars[uiIndex]->Name = elemVariable->Attribute("name");

		switch( m_ShaderVars[uiIndex]->Type )
		{
			case eTEXTURE:
				(*(r_string*)m_ShaderVars[uiIndex]->Var) = r_string(elemVariable->Attribute("value"));
				break;

			case eFLOAT:
				(*(float*)m_ShaderVars[uiIndex]->Var) = elemVariable->FloatAttribute("value");
				break;

			case eVEC2:
				(*(sf::Glsl::Vec2*)m_ShaderVars[uiIndex]->Var).x = elemVariable->FloatAttribute("valueX");
				(*(sf::Glsl::Vec2*)m_ShaderVars[uiIndex]->Var).y = elemVariable->FloatAttribute("valueY");
				break;

			case eVEC3:
				(*(sf::Glsl::Vec3*)m_ShaderVars[uiIndex]->Var).x = elemVariable->FloatAttribute("valueX");
				(*(sf::Glsl::Vec3*)m_ShaderVars[uiIndex]->Var).y = elemVariable->FloatAttribute("valueY");
				(*(sf::Glsl::Vec3*)m_ShaderVars[uiIndex]->Var).z = elemVariable->FloatAttribute("valueZ");
				break;

			case eVEC4:
				(*(sf::Glsl::Vec4*)m_ShaderVars[uiIndex]->Var).x = elemVariable->FloatAttribute("valueX");
				(*(sf::Glsl::Vec4*)m_ShaderVars[uiIndex]->Var).y = elemVariable->FloatAttribute("valueY");
				(*(sf::Glsl::Vec4*)m_ShaderVars[uiIndex]->Var).z = elemVariable->FloatAttribute("valueZ");
				(*(sf::Glsl::Vec4*)m_ShaderVars[uiIndex]->Var).w = elemVariable->FloatAttribute("valueW");
				break;

			case eCOLOR:
				(*(sf::Color*)m_ShaderVars[uiIndex]->Var).r = elemVariable->IntAttribute("valueR");
				(*(sf::Color*)m_ShaderVars[uiIndex]->Var).g = elemVariable->IntAttribute("valueG");
				(*(sf::Color*)m_ShaderVars[uiIndex]->Var).b = elemVariable->IntAttribute("valueB");
				(*(sf::Color*)m_ShaderVars[uiIndex]->Var).a = elemVariable->IntAttribute("valueA");
				break;

			default:
				break;
		}

		m_ShaderVars[uiIndex]->bChanged = true;
		uiIndex++;
		elemVariable = elemVariable->NextSiblingElement("Variable");
	}
}


void ComponentShader::releaseShaderVars()
{
	for( r_uint32 i(0); i < m_ShaderVars.size(); i++ )
		SAFE_DELETE(m_ShaderVars[i]->Var);
	m_ShaderVars.deleteAndClear();
}


void ComponentShader::setShaderParameterCurrentTexture(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader)
{
	_Shader.setUniform(_ParamName, sf::Shader::CurrentTexture);
}

void ComponentShader::setShaderParameterTexture(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader)
{
	_Shader.setUniform(_ParamName, _ComponentShader->getShaderTextures()[_ParamName].Texture);
}

void ComponentShader::setShaderParameterFloat(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader)
{
	_Shader.setUniformArray(_ParamName, (float*)_Var, 1U);
}

void ComponentShader::setShaderParameterMousePosition(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader)
{
	r_vector2f MousePos = (r_vector2f)SFMLCanvas::gameCanvas->getInputManager()->getMouse().getWindowPosition();
	MousePos.y = -MousePos.y + SFMLCanvas::gameCanvas->getSize().y;

	_Shader.setUniform(_ParamName, MousePos);
}

void ComponentShader::setShaderParameterVec2(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader)
{
	_Shader.setUniformArray(_ParamName, (sf::Glsl::Vec2*)_Var, 1U);
}

void ComponentShader::setShaderParameterVec3(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader)
{
	_Shader.setUniformArray(_ParamName, (sf::Glsl::Vec3*)_Var, 1U);
}

void ComponentShader::setShaderParameterVec4(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader)
{
	_Shader.setUniformArray(_ParamName, (sf::Glsl::Vec4*)_Var, 1U);
}

void ComponentShader::setShaderParameterColor(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader)
{
	sf::Glsl::Vec4 vColor(((sf::Color*)(_Var))->r / 255.0f, ((sf::Color*)(_Var))->g / 255.0f, ((sf::Color*)(_Var))->b / 255.0f, ((sf::Color*)(_Var))->a / 255.0f);
	_Shader.setUniformArray(_ParamName, &vColor, 1U);
}


sf::Shader* ComponentShader::getShader()
{
	return &m_Shader;
}

std::map<r_string, ComponentShader::stSHADER_TEXTURE>& ComponentShader::getShaderTextures()
{
	return m_ShaderTextures;
}