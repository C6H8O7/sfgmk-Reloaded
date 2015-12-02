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

void ComponentGameObject::OnMembersUpdate()
{
#ifdef SFGMKR_EDITOR
	MyGUI::GetGUI()->GUI_HierarchyTree->SetItemText(parent->treeID, parent->name);
#endif
}

#ifdef SFGMKR_EDITOR
void ComponentGameObject::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_STRING, "Name", &parent->name, 0);
}
#endif