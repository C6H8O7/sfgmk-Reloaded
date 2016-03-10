#include "stdafx.h"

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
	: owner(_owner)
{

}

r_bool wxMyTextDropTargetEditor::OnDropText(wxCoord _x, wxCoord _y, const wxString & _data)
{
	MyGUI* gui = MyGUI::GetGUI();

	GameObject* gameobject = new GameObject();
	gameobject->addDefaultComponents();

	gameobject->transform.setPosition(gui->GUI_EditorSFML->getInputManager()->getMouse().getWorldPosition());

	GameObject::AddAsComponent(gameobject, r_string((const r_int8*)_data.c_str()));

	SFMLCanvas::project->getCurrentScene()->addGameObject(gameobject);

	gui->selectedGameObject = gameobject;
	gui->selectedGameObjectComponent = 0;

	gui->selectedGameObject->showComponents(true);

	return false;
}

#endif