#include "stdafx.h"


namespace gmk
{
	Prefab::Prefab(tinyxml2::XMLElement* _Xml)
	{
		loadFromXml(_Xml);
	}

	Prefab::Prefab(GameObject* _Model)
	{
		//Sauvegarde en mémoire du modèle
		tinyxml2::XMLDocument Doc;
		tinyxml2::XMLElement* GameObject_elem = Doc.NewElement("GameObject");
		Doc.LinkEndChild(GameObject_elem);
		gmk::vector<GameObjectComponent*>& Components = _Model->getComponents();

		for( r_uint32 i(0); i < Components.size(); i++ )
		{
			GameObjectComponent* Component = Components[i];
			tinyxml2::XMLElement* Component_elem = Doc.NewElement("Component");
			GameObject_elem->LinkEndChild(Component_elem);
			Component_elem->SetAttribute("type", Component->type_name.c_str());
			Component->OnXMLSave(Component_elem);
		}

		GameObject_elem = Doc.FirstChildElement("GameObject");
		tinyxml2::XMLElement* Component_elem = GameObject_elem->FirstChildElement("Component");

		loadFromXml(Component_elem);
	}

	Prefab::~Prefab()
	{
		SAFE_DELETE(m_GameObject);
	}


	void Prefab::loadFromXml(tinyxml2::XMLElement* _Xml)
	{
		//Création nouvel élément depuis modèle en mémoire
		m_GameObject = new GameObject(false);

		while( _Xml )
		{
			GameObjectComponent* Component = NULL;
			r_string type = _Xml->Attribute("type");

			Component = ComponentsBank::GetSingleton()->createComponent(type, m_GameObject);

			if( Component )
			{
				Component->OnXMLLoad(_Xml);
				m_GameObject->addComponent(Component);
			}

			_Xml = _Xml->NextSiblingElement("Component");
		}
	}


	GameObject* Prefab::getGameObject()
	{
		return m_GameObject;
	}
}