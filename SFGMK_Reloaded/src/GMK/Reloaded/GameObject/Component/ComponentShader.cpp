void(*ComponentShader::setParameterFunctionsPtr[eSHADER_PROPERTY_TYPE_NUMBER])(sf::Shader&, const r_string&, void*) = { &ComponentShader::setShaderParameterTexture,
																														&ComponentShader::setShaderParameterInt,
																														&ComponentShader::setShaderParameterFloat };

ComponentShader::ComponentShader(GameObject * _parent)
	: GameObjectComponent("Shader", _parent), m_Path(""), m_PathChanged(false)
{
}

ComponentShader::~ComponentShader()
{
	m_ShaderVars.deleteAndClear();
}


r_void ComponentShader::OnUpdate(SFMLCanvas * _canvas)
{
	m_Shader.setParameter("_CurrentTexture", m_Shader.CurrentTexture);

	for( r_uint32 i(0); i < m_ShaderVars.size(); i++ )
		setParameterFunctionsPtr[0](m_Shader, m_ShaderVars[i]->Name, m_ShaderVars[i]->Var);
}

r_void ComponentShader::OnMembersUpdate()
{
	if( m_PathChanged )
	{
		m_PathChanged = false;
		m_ShaderVars.deleteAndClear();

		if( m_Path.size() )
		{
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
						Name = Name.substr(0, Name.find_first_of(' ;'));

						/*if( Type == "sampler2D" )
						{
							if( Line.find("//CurrentTexture", 0) != std::string::npos )
							{
								
								stSHADER_VAR* NewVar = new stSHADER_VAR(eSHADER_PROPERTY_TYPE::eCURRENT_TEXTURE, Name, (sf::Shader::CurrentTexture*)calloc(1, sizeof(sf::Shader::CurrentTexture*)));
							}
							else
							{
								stSHADER_VAR* NewVar = new stSHADER_VAR(eSHADER_PROPERTY_TYPE::eTEXTURE, Name, (r_string*)calloc(1, sizeof(r_string*)));
								m_ShaderVars.push_back(NewVar);
							}
						}*/
						 if( Type == "int" )
						{
							stSHADER_VAR* NewVar = new stSHADER_VAR(eSHADER_PROPERTY_TYPE::eINT, Name, (r_uint32*)calloc(1, sizeof(r_uint32*)));
							m_ShaderVars.push_back(NewVar);
						}
						else if( Type == "float" )
						{
							stSHADER_VAR* NewVar = new stSHADER_VAR(eSHADER_PROPERTY_TYPE::eFLOAT, Name, (float*)calloc(1, sizeof(float*)));
							m_ShaderVars.push_back(NewVar);
						}
						/*else if( Type == "bool" )
						{
							stSHADER_VAR* NewVar = new stSHADER_VAR(ePROPERTY_TYPE::TYPE_FLOAT, Name, (r_bool*)calloc(1, sizeof(r_bool*)));
							m_ShaderVars.push_back(NewVar);
						}*/

						/*
						vec2
						vec3: vecteur à 3 composantes flottantes;
						vec4: vecteur à 4 composantes flottantes;
						mat2: matrice 2 * 2 de flottants;
						mat3: matrice 3 * 3 de flottants;
						mat4: matrice 4 * 4 de flottants;
						ivec2: vecteur à 2 composantes entières;
						ivec3: vecteur à 3 composantes entières;
						ivec4: vecteur à 4 composantes entières;
						bvec2: vecteur à 2 composantes booléennes;
						bvec3: vecteur à 3 composantes booléennes;
						bvec4: vecteur à 4 composantes booléennes.*/
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

	for( r_uint32 i(0); i < m_ShaderVars.size(); i++ )
	{
		switch( m_ShaderVars[i]->Type )
		{
			/*case eTEXTURE:
				registerProperty(ePROPERTY_TYPE::TYPE_STRING, m_ShaderVars[i]->Name, m_ShaderVars[i]->Var);
				break;*/

			case eINT:
				registerProperty(ePROPERTY_TYPE::TYPE_INT, m_ShaderVars[i]->Name, m_ShaderVars[i]->Var);
				break;

			case eFLOAT:
				registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, m_ShaderVars[i]->Name, m_ShaderVars[i]->Var);
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
	_element->SetAttribute("Path", m_Path.c_str());
	
	for( r_uint32 i(0); i < m_ShaderVars.size(); i++ )
	{
		switch( m_ShaderVars[i]->Type )
		{
			/*case eTEXTURE:
				_element->SetAttribute(m_ShaderVars[i]->Name.c_str(), *(int*)m_ShaderVars[i]->Var);
				break;*/

			case eINT:
				_element->SetAttribute(m_ShaderVars[i]->Name.c_str(), *(int*)m_ShaderVars[i]->Var);
				break;

			case eFLOAT:
				_element->SetAttribute(m_ShaderVars[i]->Name.c_str(), *(float*)m_ShaderVars[i]->Var);
				break;
		}
	}
}

r_void ComponentShader::OnXMLLoad(tinyxml2::XMLElement * _element)
{
	m_Path = _element->Attribute("Path");
	m_PathChanged = true;
}


void ComponentShader::setShaderParameterTexture(sf::Shader& _Shader, const r_string& _ParamName, void* _Var)
{
	_Shader.setParameter(_ParamName, (sf::Texture)(*(sf::Texture*)_Var));
}

void ComponentShader::setShaderParameterInt(sf::Shader& _Shader, const r_string& _ParamName, void* _Var)
{
	_Shader.setParameter(_ParamName, (int)(*(int*)_Var));
}

void ComponentShader::setShaderParameterFloat(sf::Shader& _Shader, const r_string& _ParamName, void* _Var)
{
	_Shader.setParameter(_ParamName, (float)(*(float*)_Var));
}

sf::Shader* ComponentShader::getShader()
{
	return &m_Shader;
}