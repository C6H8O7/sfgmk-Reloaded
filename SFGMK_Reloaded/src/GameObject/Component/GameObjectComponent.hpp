#ifndef SFGMKR_GAMEOBJECTCOMPONENT_HPP
#define SFGMKR_GAMEOBJECTCOMPONENT_HPP

class GameObject;

class GameObjectComponent
{
protected:

	enum ePROPERTY_TYPE
	{
		TYPE_CATEGORY,
		TYPE_STRING,
		TYPE_INT,
		TYPE_FLOAT
	};

	struct ComponentProperty
	{
		wxPGProperty* wxProperty;
		ePROPERTY_TYPE type;
		std::string name;
		void* data;
		bool* changed;
	};

	sfgmk::vector<ComponentProperty*> m_Properties;

	void beginRegister();
	void registerProperty(ePROPERTY_TYPE _type, std::string _name, void* _pData, bool* _pChanged = 0);
	void endRegister();

public:

	GameObjectComponent(std::string _type, GameObject* _parent);
	~GameObjectComponent();

	virtual void OnUpdate();
	virtual void OnDraw();

	virtual void OnRegistration();
	virtual void OnPropertiesApparition();
	virtual void OnPropertiesDisapparition();
	virtual void OnUnegistration();

	virtual void OnPropertyGridChanged(wxPropertyGridEvent& _event);

	GameObject* parent;

	bool active;

	std::string type;
	bool unique;
};

#endif