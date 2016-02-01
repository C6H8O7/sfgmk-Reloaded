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
		
		Xml.LoadFile(Path.c_str());
		tinyxml2::XMLElement* PrefabsElements = Xml.FirstChildElement("Prefabs");

		//Si pas de prefabs
		if( !PrefabsElements )
			return;

		//Récupération liste des prefabs
		tinyxml2::XMLElement* PrefabElement = PrefabsElements->FirstChildElement("Prefab");
		vector<r_string> PrefabList;

		while( PrefabElement )
		{
			Prefab* NewPrefab = new Prefab(PrefabElement->FirstChildElement("Component"));
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
			GameObject* NewGameObject = new GameObject(false);

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

			createPrefab(NewGameObject);
			delete NewGameObject;
		}

		PrefabList.clear();
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

	r_bool Factory::createPrefab(GameObject* _Model)
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

		r_string Path = "../../project/prefabs/" + _Model->name + ".prefab";
		Xml.SaveFile(Path.c_str());

		savePrefabs("../../project/prefabs/PrefabList.prefabs");

		return true;
	}

	r_bool Factory::removePrefab(const r_string& _PrefabId)
	{
		std::unordered_map<r_string, Prefab*>::iterator Element;

		//Check if prefab exists
		if( (Element = m_Prefabs.find(_PrefabId)) == m_Prefabs.end() )
			return false;

		//Delete prefab
		delete (*Element).second;
		m_Prefabs.erase(_PrefabId);

		return true;
	}


	GameObject* Factory::instantiate(const r_string& _PrefabId, GameObject* _NewGameObject)
	{
		std::unordered_map<r_string, Prefab*>::iterator Element;
		if( (Element = m_Prefabs.find(_PrefabId)) != m_Prefabs.end() )
		{
			//Sauvegarde en mémoire du modèle
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

			//Création nouvel élément depuis modèle en mémoire
			GameObject* NewGameObject(NULL);
			if( _NewGameObject )
				NewGameObject = _NewGameObject;
			else
				NewGameObject = new GameObject(false);

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

			//Ajout scène
			if( !_NewGameObject )
			{
				SFMLCanvas::project->getCurrentScene()->addGameObject(NewGameObject);
				MyGUI::GetGUI()->Update_HierarchyTree();
				MyGUI::GetGUI()->Update_PropertyGrid();
			}

			return NewGameObject;
		}
		else
			return NULL;
	}
}