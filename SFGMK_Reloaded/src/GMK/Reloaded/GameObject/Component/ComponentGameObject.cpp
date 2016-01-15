#include "stdafx.h"

ComponentGameObject::ComponentGameObject(GameObject * _parent)
	: GameObjectComponent("GameObject", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentGameObject::~ComponentGameObject()
{

}

r_void ComponentGameObject::OnMembersUpdate()
{
#ifdef SFGMKR_EDITOR
	if(parent->treeID)
		MyGUI::GetGUI()->GUI_HierarchyTree->SetItemText(parent->treeID, parent->name);
#endif
}

#ifdef SFGMKR_EDITOR
r_void ComponentGameObject::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Name", &parent->name, 0);
}
#endif

r_void ComponentGameObject::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("name", parent->name.c_str());
}

r_void ComponentGameObject::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	parent->name = _element->Attribute("name");
}