#ifndef SFGMKR_GAMEOBJECTCOMPONENT_HPP
#define SFGMKR_GAMEOBJECTCOMPONENT_HPP

class GameObject;
class SFMLCanvas;

class GameObjectComponent
{
#ifdef SFGMKR_EDITOR
	friend class MyGUI;
#endif
protected:

	enum eCOMPONENT_TYPE
	{
		TYPE_SPRITE,
		TYPE_SCRIPT,
		TYPE_CAMERA
	};

#ifdef SFGMKR_EDITOR
	enum ePROPERTY_TYPE
	{
		TYPE_CATEGORY,
		TYPE_STRING,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_COLOR,
		TYPE_BOOL
	};

	struct ComponentProperty
	{
		wxPGProperty* wxProperty;
		ePROPERTY_TYPE type;
		std::string name;
		void* data;
		bool* changed;
	};

	gmk::vector<ComponentProperty*> m_Properties;

	void beginRegister();
	void registerProperty(ePROPERTY_TYPE _type, std::string _name, void* _pData, bool* _pChanged = 0);
	void endRegister();
#endif

public:

	GameObjectComponent(std::string _typeName, GameObject* _parent);
	virtual ~GameObjectComponent();

	virtual void OnUpdate(SFMLCanvas * _canvas);
	virtual void OnMembersUpdate();
	virtual void OnComponentUpdate(SFMLCanvas * _canvas);
	virtual void OnDraw(SFMLCanvas* _canvas);

#ifdef SFGMKR_EDITOR
	virtual void OnRegistration();
	virtual void OnPropertiesUpdate();
	virtual void OnPropertiesApparition();
	virtual void OnPropertiesDisapparition();
	virtual void OnUnegistration();

	virtual void OnPropertyGridChanged(wxPropertyGridEvent& _event);

	virtual void OnEditorUpdate();
#endif

	virtual void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual void OnXMLLoad(tinyxml2::XMLElement* _element);

	GameObject* parent;

	bool active;

	std::string type_name;
	bool unique;

	bool deletion;
};

#endif