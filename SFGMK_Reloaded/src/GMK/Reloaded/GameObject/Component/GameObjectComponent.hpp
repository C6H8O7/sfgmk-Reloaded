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
		r_string name;
		r_void* data;
		r_bool* changed;
	};

	gmk::vector<ComponentProperty*> m_Properties;

	r_void beginRegister();
	r_void registerProperty(ePROPERTY_TYPE _type, r_string _name, r_void* _pData, r_bool* _pChanged = 0);
	r_void endRegister();
#endif

public:

	GameObjectComponent(r_string _typeName, GameObject* _parent);
	virtual ~GameObjectComponent();

	virtual r_void OnUpdate(SFMLCanvas * _canvas);
	virtual r_void OnMembersUpdate();
	virtual r_void OnComponentUpdate(SFMLCanvas * _canvas);
	virtual r_void OnDraw(SFMLCanvas* _canvas);

#ifdef SFGMKR_EDITOR
	virtual r_void OnRegistration();
	virtual r_void OnPropertiesUpdate();
	virtual r_void OnPropertiesApparition();
	virtual r_void OnPropertiesDisapparition();
	virtual r_void OnUnegistration();

	virtual r_void OnPropertyGridChanged(wxPropertyGridEvent& _event);

	virtual r_void OnEditorUpdate();
#endif

	virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
	virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	GameObject* parent;

	r_bool active;

	r_string type_name;
	r_bool unique;

	r_bool deletion;
};

#endif