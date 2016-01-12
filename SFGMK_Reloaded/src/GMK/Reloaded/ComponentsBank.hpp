#ifndef SFGMKR_COMPONENTSBANK_HPP
#define SFGMKR_COMPONENTSBANK_HPP

class ComponentsBank
{
protected:

	union sCOMPONENT_CREATION
	{
		r_void* void_ptr;
		GameObjectComponent* (*component_ctor)(GameObject* _gameobject);
	};

	struct sCOMPONENT
	{
		r_string name;
		sCOMPONENT_CREATION creation;
	};

	ComponentsBank();
	~ComponentsBank();

	gmk::vector<sCOMPONENT*> m_Components;

public:

	static ComponentsBank* GetSingleton();

	template <class T>
	r_void registerComponent(r_string _name)
	{
		sCOMPONENT component;
		component.name = _name;
		component.creation.void_ptr = &creationFunc<T>;

		bool found = false;

		for (r_uint32 i = 0; i < m_Components.size(); i++)
			if (m_Components[i]->name == _name)
				found = true;

		if (!found)
			m_Components.push_back(new sCOMPONENT(component));
	}

	r_void unregisterComponent(r_string _name);

	template <class T>
	friend T* creationFunc(GameObject* _gameobject)
	{
		return new T(_gameobject);
	}

	GameObjectComponent* createComponent(r_string _name, GameObject* _parent);

	r_void registerAllComponents();
};

#endif