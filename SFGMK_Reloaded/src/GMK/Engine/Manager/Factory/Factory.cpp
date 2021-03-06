#include "stdafx.h"


namespace gmk
{
	Factory::Factory()
	{
	}

	Factory::~Factory()
	{
		for( auto it = m_Prefabs.begin(); it != m_Prefabs.end(); ++it )
			delete (*it).second;
		m_Prefabs.clear();

		m_PrefabsAccount.clear();
	}


	r_void Factory::loadPrefabs(const r_string& _Path)
	{
		tinyxml2::XMLDocument Xml;
		r_string Path = _Path + "/PrefabList.prefabs";

		gmk::Debug::Log("[INFO] Loading prefabs : " + Path);
		
		Xml.LoadFile(Path.c_str());
		tinyxml2::XMLElement* PrefabsElements = Xml.FirstChildElement("Prefabs");

		//Si pas de prefabs
		if( !PrefabsElements )
		{
			if( SFGMKR_FACTORY_DEBUG )
				std::cout << "[INFO] Factory : no prefabs to load " << std::endl;
			return;
		}

		//R�cup�ration liste des prefabs
		tinyxml2::XMLElement* PrefabElement = PrefabsElements->FirstChildElement("Prefab");
		std::vector<r_string> PrefabList;

		while( PrefabElement )
		{
			PrefabList.push_back(PrefabElement->Attribute("id"));
			PrefabElement = PrefabElement->NextSiblingElement();
		}

		//Chargement de chaque prefab
		for( r_uint32 i(0U); i < PrefabList.size(); i++ )
		{
			Path = _Path + "/" + PrefabList[i] + ".prefab";
			Xml.LoadFile(Path.c_str());

			PrefabElement = Xml.FirstChildElement("Prefab");
			tinyxml2::XMLElement* ComponentElement = PrefabElement->FirstChildElement();

			GameObject* NewGameObject = new GameObject();
			NewGameObject->isPrefab = true;

			//Chargement de chaque component
			while( ComponentElement )
			{
				GameObjectComponent* NewComponent = NULL;
				r_string ComponentType = ComponentElement->Attribute("type");
				NewComponent = ComponentsBank::GetSingleton()->createComponent(ComponentType, NewGameObject);

				if( NewComponent )
				{
					NewComponent->OnXMLLoad(ComponentElement);
					NewGameObject->addComponent(NewComponent);
				}

				ComponentElement = ComponentElement->NextSiblingElement();
			}

			createPrefab(NewGameObject, false);
			delete NewGameObject;
		}

		PrefabList.clear();

		if( SFGMKR_FACTORY_DEBUG )
			std::cout << "[INFO] Factory : prefabs loaded " << std::endl;
	}

	r_void Factory::savePrefabs(const r_string& _Path)
	{
		tinyxml2::XMLDocument Xml;

		tinyxml2::XMLDeclaration* Declaration = Xml.NewDeclaration(0);
		Xml.LinkEndChild(Declaration);

		tinyxml2::XMLElement* PrefabsElement = Xml.NewElement("Prefabs");
		Xml.LinkEndChild(PrefabsElement);

		for( auto it(m_Prefabs.begin()); it != m_Prefabs.end(); ++it)
		{
			tinyxml2::XMLElement* PrefabElement = Xml.NewElement("Prefab");
			PrefabsElement->LinkEndChild(PrefabElement);

			PrefabElement->SetAttribute("id", it->first.c_str());
		}

		Xml.SaveFile(_Path.c_str());
	}

	r_bool Factory::addPrefabToBank(GameObject* _Model)
	{
		//Check if prefab with same name already exists
		if( m_Prefabs.find(_Model->name) != m_Prefabs.end() )
			return false;

		m_Prefabs[_Model->name] = new Prefab(_Model);
		m_PrefabsAccount[_Model->name] = 0U;
		return true;
	}

	r_bool Factory::createPrefab(GameObject* _Model, bool _save)
	{
		//Create new prefab
		if( !addPrefabToBank(_Model) )
			return false;

		//Create file
		tinyxml2::XMLDocument Xml;
		tinyxml2::XMLDeclaration* Declaration = Xml.NewDeclaration(0);
		Xml.LinkEndChild(Declaration);
		tinyxml2::XMLElement* PrefabElement = Xml.NewElement("Prefab");
		Xml.LinkEndChild(PrefabElement);

		gmk::vector<GameObjectComponent*>& components = m_Prefabs[_Model->name]->getGameObject()->getComponents();

		for( r_uint32 i(0U); i < components.size(); i++ )
		{
			GameObjectComponent* Component = components[i];

			tinyxml2::XMLElement* ComponentElement = Xml.NewElement("Component");
			PrefabElement->LinkEndChild(ComponentElement);
			ComponentElement->SetAttribute("type", Component->type_name.c_str());
			Component->OnXMLSave(ComponentElement);
		}

		r_string Path = SFMLCanvas::project->getPrefabsPath() + "/" + _Model->name + ".prefab";
		Xml.SaveFile(Path.c_str());

		if (_save) savePrefabs(SFMLCanvas::project->getPrefabsPath() + "/PrefabList.prefabs");
		
		return true;
	}

	r_bool Factory::removePrefab(const r_string& _PrefabId)
	{
		std::unordered_map<r_string, Prefab*>::iterator Element;

		//Check if prefab exists
		if( (Element = m_Prefabs.find(_PrefabId)) == m_Prefabs.end() )
			return false;

		//Delete fichier
		remove(r_string(SFMLCanvas::project->getPrefabsPath()  + "/" + _PrefabId + ".prefab").c_str());

		//Delete prefab
		delete (*Element).second;
		m_Prefabs.erase(_PrefabId);

		return true;
	}

	r_bool Factory::applyChangesToPrefab(GameObject* _Model)
	{
		delete m_Prefabs[_Model->name];
		m_Prefabs[_Model->name] = new Prefab(_Model);

		//Create file
		tinyxml2::XMLDocument Xml;
		tinyxml2::XMLDeclaration* Declaration = Xml.NewDeclaration(0);
		Xml.LinkEndChild(Declaration);
		tinyxml2::XMLElement* PrefabElement = Xml.NewElement("Prefab");
		Xml.LinkEndChild(PrefabElement);

		gmk::vector<GameObjectComponent*>& components = m_Prefabs[_Model->name]->getGameObject()->getComponents();

		for( r_uint32 i(0U); i < components.size(); i++ )
		{
			GameObjectComponent* Component = components[i];

			tinyxml2::XMLElement* ComponentElement = Xml.NewElement("Component");
			PrefabElement->LinkEndChild(ComponentElement);
			ComponentElement->SetAttribute("type", Component->type_name.c_str());
			Component->OnXMLSave(ComponentElement);
		}

		r_string Path = SFMLCanvas::project->getPrefabsPath() + "/" + _Model->name + ".prefab";
		Xml.SaveFile(Path.c_str());

		return true;
	}


	GameObject* Factory::instantiate(const r_string& _PrefabId, GameObject* _NewGameObject)
	{
		std::unordered_map<r_string, Prefab*>::iterator Element;
		if( (Element = m_Prefabs.find(_PrefabId)) != m_Prefabs.end() )
		{
			//Sauvegarde en m�moire du mod�le
			tinyxml2::XMLDocument Doc;
			tinyxml2::XMLElement* GameObject_elem = Doc.NewElement("GameObject");
			Doc.LinkEndChild(GameObject_elem);
			gmk::vector<GameObjectComponent*>& Components = Element->second->getGameObject()->getComponents();

			for( r_uint32 i(0); i < Components.size(); i++ )
			{
				GameObjectComponent* Component = Components[i];
				tinyxml2::XMLElement* Component_elem = Doc.NewElement("Component");
				GameObject_elem->LinkEndChild(Component_elem);
				Component_elem->SetAttribute("type", Component->type_name.c_str());
				Component->OnXMLSave(Component_elem);
			}

			//Cr�ation nouvel �l�ment depuis mod�le en m�moire
			GameObject* NewGameObject(NULL);
			if( _NewGameObject )
				NewGameObject = _NewGameObject;
			else
				NewGameObject = new GameObject();

			NewGameObject->prefabID = _PrefabId;

			GameObject_elem = Doc.FirstChildElement("GameObject");
			tinyxml2::XMLElement* Component_elem = GameObject_elem->FirstChildElement("Component");

			while( Component_elem )
			{
				GameObjectComponent* Component = NULL;
				r_string type = Component_elem->Attribute("type");

				Component = ComponentsBank::GetSingleton()->createComponent(type, NewGameObject);

				if( Component )
				{
					Component->OnXMLLoad(Component_elem);
					Component->OnMembersUpdate();
					NewGameObject->addComponent(Component);
				}

				Component_elem = Component_elem->NextSiblingElement("Component");
			}

			m_PrefabsAccount[_PrefabId]++;
			NewGameObject->name += std::to_string(m_PrefabsAccount[_PrefabId]);

			//Ajout sc�ne
			if( !_NewGameObject )
				SFMLCanvas::project->getCurrentScene()->addGameObject(NewGameObject);

			return NewGameObject;
		}
		else
			return NULL;
	}


	GameObject* Factory::duplicate(GameObject* _selectedGameObject)
	{
		//Sauvegarde en m�moire du mod�le
		tinyxml2::XMLDocument Doc;
		tinyxml2::XMLElement* GameObject_elem = Doc.NewElement("GameObject");
		Doc.LinkEndChild(GameObject_elem);
		gmk::vector<GameObjectComponent*>& Components = _selectedGameObject->getComponents();

		for( r_uint32 i(0); i < Components.size(); i++ )
		{
			GameObjectComponent* Component = Components[i];
			tinyxml2::XMLElement* Component_elem = Doc.NewElement("Component");
			GameObject_elem->LinkEndChild(Component_elem);
			Component_elem->SetAttribute("type", Component->type_name.c_str());
			Component->OnXMLSave(Component_elem);
		}

		//Cr�ation nouvel �l�ment depuis mod�le en m�moire
		GameObject* SelectedObjectCopy = new GameObject();

		GameObject_elem = Doc.FirstChildElement("GameObject");
		tinyxml2::XMLElement* Component_elem = GameObject_elem->FirstChildElement("Component");

		while( Component_elem )
		{
			GameObjectComponent* Component = NULL;
			r_string type = Component_elem->Attribute("type");

			Component = ComponentsBank::GetSingleton()->createComponent(type, SelectedObjectCopy);

			if( Component )
			{
				Component->OnXMLLoad(Component_elem);
				Component->OnMembersUpdate();
				SelectedObjectCopy->addComponent(Component);
			}

			Component_elem = Component_elem->NextSiblingElement("Component");
		}

		SelectedObjectCopy->name += "cpy";

		return SelectedObjectCopy;
	}


	r_bool Factory::prefabExists(const r_string& _Name)
	{
		if( m_Prefabs.find(_Name) != m_Prefabs.end() )
			return true;

		return false;
	}
}