#include "wxMyTextDropTarget.hpp"
#ifdef SFGMKR_EDITOR

wxMyTextDropTargetProperties::wxMyTextDropTargetProperties(wxPropertyGrid * _owner)
	: owner(_owner)
{

}

bool wxMyTextDropTargetProperties::OnDropText(wxCoord _x, wxCoord _y, const wxString & _data)
{
	GameObject::AddAsComponent(MyGUI::GetGUI()->selectedGameObject, std::string(_data.c_str()));

	return true;
}

wxMyTextDropTargetEditor::wxMyTextDropTargetEditor(SFMLEditorCanvas * _owner)
{

}

bool wxMyTextDropTargetEditor::OnDropText(wxCoord _x, wxCoord _y, const wxString & _data)
{
	MyGUI* gui = MyGUI::GetGUI();

	GameObject* gameobject = new GameObject();

	sf::Vector2f world_position = gui->GUI_EditorSFML->getInputManager()->getMouse().getWorldPosition();

	gameobject->transform.position = world_position;

	GameObject::AddAsComponent(gameobject, std::string((const char*)_data.c_str()));

	SFMLCanvas::project->getCurrentScene()->addGameObject(gameobject);

	gui->selectedGameObject = gameobject;

	gui->Update_HierarchyTree();
	gui->Update_PropertyGrid();

	return false;
}

#endif