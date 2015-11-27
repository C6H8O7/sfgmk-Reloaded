MyGUI::MyGUI(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: GUI_MainFrame(parent, id, title, pos, size, style)
{
	selectedGameObject = 0;
}

void MyGUI::GUI_PanelPreview_OnSize(wxSizeEvent& _event)
{
	int w = GUI_PanelPreview->GetSize().GetWidth();
	int h = GUI_PanelPreview->GetSize().GetHeight();

	float fw = w / SFGMKR_DEFAULT_SFML_SIZE_X;
	float fh = h / SFGMKR_DEFAULT_SFML_SIZE_Y;

	float f = fw > fh ? fh : fw;

	float nw = f * SFGMKR_DEFAULT_SFML_SIZE_X;
	float nh = f * SFGMKR_DEFAULT_SFML_SIZE_Y;

	GUI_PreviewSFML->SetSize(_event.GetSize());

	GUI_PreviewSFML->setSize(sf::Vector2u(nw, nh));
	GUI_PreviewSFML->setPosition(sf::Vector2i(0.5f * (w - nw), 0.5f * (h - nh)));
}

void MyGUI::Update_HierarchyTree()
{
	GUI_HierarchyTree->DeleteAllItems();

	wxTreeItemId treeid = GUI_HierarchyTree->AddRoot("Scene");

	sfgmk::vector<GameObject*>& gameobjects = GameObjectManager::GetSingleton()->getGameObjects();

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
	{
		GameObject* gameobject = gameobjects[i];

		gameobject->treeID = GUI_HierarchyTree->AppendItem(treeid, gameobject->name).GetID();
	}
}

void MyGUI::GUI_HierarchyTree_OnTreeEndLabelEdit(wxTreeEvent& _event)
{
	GameObject* gameobject = GameObjectManager::GetSingleton()->findGameObjectByTreeID(_event.GetItem().GetID());

	if (gameobject)
	{
		gameobject->name = std::string(_event.GetLabel().c_str());
	}
}

void MyGUI::GUI_HierarchyTree_OnTreeSelChanged(wxTreeEvent& _event)
{
	selectedGameObject = GameObjectManager::GetSingleton()->findGameObjectByTreeID(_event.GetItem().GetID());

	if (!selectedGameObject)
		return;

	printf("%s (%f; %f)\n", selectedGameObject->name.c_str(), selectedGameObject->transform.position.x, selectedGameObject->transform.position.y);

	GUI_PosX->SetValue(wxString(std::to_string(selectedGameObject->transform.position.x)));
	GUI_PosY->SetValue(wxString(std::to_string(selectedGameObject->transform.position.y)));
	GUI_ScaleX->SetValue(wxString(std::to_string(selectedGameObject->transform.scale.x)));
	GUI_ScaleY->SetValue(wxString(std::to_string(selectedGameObject->transform.scale.y)));
	GUI_Rotation->SetValue(wxString(std::to_string(selectedGameObject->transform.rotation)));
}

void MyGUI::GUI_MenuGameObjectCreateEmpty_OnMenuSelection(wxCommandEvent& _event)
{
	printf("adding gameobject\n");

	GameObjectManager::GetSingleton()->addGameObject(new GameObject());

	Update_HierarchyTree();
}

void MyGUI::GUI_PosX_OnText(wxCommandEvent& _event)
{
	if (selectedGameObject)
		selectedGameObject->transform.position.x = (float)std::atof(GUI_PosX->GetValue().c_str());
}

void MyGUI::GUI_PosY_OnText(wxCommandEvent& _event)
{

	if (selectedGameObject)
		selectedGameObject->transform.position.y = (float)std::atof(GUI_PosY->GetValue().c_str());
}

void MyGUI::GUI_ScaleX_OnText(wxCommandEvent& _event)
{
	if (selectedGameObject)
		selectedGameObject->transform.scale.x = (float)std::atof(GUI_ScaleX->GetValue().c_str());
}

void MyGUI::GUI_ScaleY_OnText(wxCommandEvent& _event)
{
	if (selectedGameObject)
		selectedGameObject->transform.scale.y = (float)std::atof(GUI_ScaleY->GetValue().c_str());
}

void MyGUI::GUI_Rotation_OnText(wxCommandEvent& _event)
{
	if (selectedGameObject)
		selectedGameObject->transform.rotation = (float)std::atof(GUI_Rotation->GetValue().c_str());
}