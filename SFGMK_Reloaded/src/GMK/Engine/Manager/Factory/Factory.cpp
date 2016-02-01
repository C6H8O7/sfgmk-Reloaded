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
	}


	r_void Factory::loadPrefabs(const r_string& _Path)
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(_Path.c_str());
		tinyxml2::XMLElement* PrefabsElem = doc.FirstChildElement("Prefabs");

		if( !PrefabsElem )
			return;

		tinyxml2::XMLElement* PrefabElem = PrefabsElem->FirstChildElement("Prefab");

		while( PrefabElem )
		{
			Prefab* NewPrefab = new Prefab(PrefabElem->FirstChildElement("Component"));
			m_Prefabs[NewPrefab->getGameObject()->name] = NewPrefab;

			PrefabElem = PrefabElem->NextSiblingElement();
		}
	}

	r_void Factory::savePrefabs(const r_string& _Path)
	{
		tinyxml2::XMLDocument doc;

		tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration(0);
		doc.LinkEndChild(declaration);

		tinyxml2::XMLElement* gameobjects_elem = doc.NewElement("Prefabs");
		doc.LinkEndChild(gameobjects_elem);

		for( auto it(m_Prefabs.begin()); it != m_Prefabs.end(); ++it)
		{
			GameObject* gameobject = (*it).second->getGameObject();

			tinyxml2::XMLElement* gameobject_elem = doc.NewElement("Prefab");
			gameobjects_elem->LinkEndChild(gameobject_elem);

			gmk::vector<GameObjectComponent*>& components = gameobject->getComponents();

			for( r_uint32 i(0U); i < components.size(); i++ )
			{
				GameObjectComponent* component = components[i];

				tinyxml2::XMLElement* component_elem = doc.NewElement("Component");
				gameobject_elem->LinkEndChild(component_elem);
				component_elem->SetAttribute("type", component->type_name.c_str());
				component->OnXMLSave(component_elem);
			}
		}

		doc.SaveFile(_Path.c_str());
	}

	r_bool Factory::createPrefab(GameObject* _Model)
	{
		//Check if prefab with same name already exists
		if( m_Prefabs.find(_Model->name) != m_Prefabs.end() )
			return false;

		//Create new prefab
		m_Prefabs[_Model->name] = new Prefab(_Model);
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


	GameObject* Factory::instantiate(const r_string& _PrefabId)
	{

		/*
		if( m_InputManager->getKeyboard().getKeyState(sf::Keyboard::A) == KEY_PRESSED )
		{
			std::cout << "PRESS" << std::endl;
			gmk::Factory::getSingleton()->instantiate("PrefabTest1");
		}
		*/


		std::unordered_map<r_string, Prefab*>::iterator Element;
		if( (Element = m_Prefabs.find(_PrefabId)) != m_Prefabs.end() )
		{
			std::cout << "INSTANTIATE " << _PrefabId << std::endl;

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
			GameObject* SelectedObjectCopy = new GameObject(false);

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

			//Ajout scène
			SFMLCanvas::project->getCurrentScene()->addGameObject(SelectedObjectCopy);
			MyGUI::GetGUI()->Update_HierarchyTree();
			MyGUI::GetGUI()->Update_PropertyGrid();

			return SelectedObjectCopy;
		}
		else
			return NULL;
	}
}