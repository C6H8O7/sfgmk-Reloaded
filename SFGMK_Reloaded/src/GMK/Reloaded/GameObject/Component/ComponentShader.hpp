/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		08/01/2016
	@brief		Component shader

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENTSHADER_HPP
#define SFGMKR_COMPONENTSHADER_HPP


class ComponentShader : public GameObjectComponent
{
	friend class GameObject;

	public:
		ComponentShader(GameObject* _parent);
		~ComponentShader();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);
		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();
		virtual r_void OnEditorUpdate();
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

		enum eSHADER_PROPERTY_TYPE
		{
			eCURRENT_TEXTURE = 0,
			eTEXTURE,
			eINT,
			eFLOAT,
			eBOOL,
			eVEC2,
			eVEC3,
			eVEC4,
			eCOLOR,
			eSHADER_PROPERTY_TYPE_NUMBER
		};

		struct stSHADER_VAR
		{
			eSHADER_PROPERTY_TYPE Type;
			r_string Name;
			void* Var;

			stSHADER_VAR(const eSHADER_PROPERTY_TYPE& _Type = (eSHADER_PROPERTY_TYPE) - 1, const r_string& _Name = "", void* _Var = NULL) : Type(_Type), Name(_Name), Var(_Var) {}
		};

		struct stSHADER_TEXTURE
		{
			sf::Uint32 uiVectorIndex;
			r_bool bChanged;
			sf::Texture Texture;

			stSHADER_TEXTURE() : uiVectorIndex(0U), bChanged(false) {}
			stSHADER_TEXTURE(const sf::Uint32& _Index, const r_bool& _Boolean = false) : uiVectorIndex(_Index), bChanged(_Boolean) {}
		};

		void releaseShaderVars();

		static void(*setParameterFunctionsPtr[eSHADER_PROPERTY_TYPE_NUMBER])(sf::Shader&, const r_string&, void*, ComponentShader*);
		static void setShaderParameterCurrentTexture(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader);
		static void setShaderParameterTexture(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader);
		static void setShaderParameterInt(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader);
		static void setShaderParameterFloat(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader);
		static void setShaderParameterBool(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader);
		static void setShaderParameterVec2(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader);
		static void setShaderParameterVec3(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader);
		static void setShaderParameterVec4(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader);
		static void setShaderParameterColor(sf::Shader& _Shader, const r_string& _ParamName, void* _Var, ComponentShader* _ComponentShader);

		sf::Shader* getShader();
		std::map<r_string, stSHADER_TEXTURE>& getShaderTextures();

	private:
		r_string m_Path;
		r_bool m_PathChanged;

		sf::Shader m_Shader;

		gmk::vector<stSHADER_VAR*> m_ShaderVars;
		std::map<r_string, stSHADER_TEXTURE> m_ShaderTextures;
};


#endif