#include "wxMyTextDropTarget.hpp"
#ifdef SFGMKR_EDITOR

wxMyTextDropTargetProperties::wxMyTextDropTargetProperties(wxPropertyGrid * _owner)
	: owner(_owner)
{

}

r_bool wxMyTextDropTargetProperties::OnDropText(wxCoord _x, wxCoord _y, const wxString & _data)
{
	GameObject* selectedGameObject = MyGUI::GetGUI()->selectedGameObject;

	if (!selectedGameObject)
		return false;

	GameObject::AddAsComponent(selectedGameObject, r_string(_data.c_str()));

	return true;
}

wxMyTextDropTargetEditor::wxMyTextDropTargetEditor(SFMLEditorCanvas * _owner)
{

}

r_bool wxMyTextDropTargetEditor::OnDropText(wxCoord _x, wxCoord _y, const wxString & _data)
{
	MyGUI* gui = MyGUI::GetGUI();

	GameObject* gameobject = new GameObject();

	r_vector2f world_position = gui->GUI_EditorSFML->getInputManager()->getMouse().getWorldPosition();

	gameobject->transform.position = world_position;

	GameObject::AddAsComponent(gameobject, r_string((const r_int8*)_data.c_str()));

	SFMLCanvas::project->getCurrentScene()->addGameObject(gameobject);

	gui->selectedGameObject = gameobject;

	gui->Update_HierarchyTree();
	gui->Update_PropertyGrid();

	return false;
}

#endif