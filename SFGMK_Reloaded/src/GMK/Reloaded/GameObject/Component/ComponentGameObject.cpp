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
	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Tag", &parent->tag, 0);
	registerProperty(ePROPERTY_TYPE::TYPE_BUTTON, "Make a Prefab", 0, 0, false, (wxObjectEventFunction)&ComponentGameObject::MakeItPrefab);
}


r_void ComponentGameObject::MakeItPrefab(wxEvent& _event)
{
	//Si le prefab existe d�j�, on demande confirmation avant d'�craser
	if( gmk::Factory::getSingleton()->prefabExists(parent->name) )
	{
		wxMessageDialog Dialog(NULL, "Prefab already exists. Apply changes?", "Warning", wxYES_NO | wxICON_WARNING);
		if( Dialog.ShowModal() == wxID_YES )
			gmk::Factory::getSingleton()->applyChangesToPrefab(parent);
	}
	else
		gmk::Factory::getSingleton()->createPrefab(parent);
}
#endif

r_void ComponentGameObject::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("name", parent->name.c_str());
	_element->SetAttribute("tag", parent->tag.c_str());
}

r_void ComponentGameObject::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	if (const char* name = _element->Attribute("name"))
		parent->name = name;

	if (const char* tag = _element->Attribute("tag"))
		parent->tag = tag;
}