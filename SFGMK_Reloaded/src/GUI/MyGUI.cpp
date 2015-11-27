MyGUI::MyGUI(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: GUI_MainFrame(parent, id, title, pos, size, style)
{
	wxTreeItemId treeid = GUI_HierarchyTree->AddRoot("Scene");
}

void MyGUI::GUI_PanelPreview_OnSize(wxSizeEvent& _event)
{
	int w = GUI_PanelPreview->GetSize().GetWidth();
	int h = GUI_PanelPreview->GetSize().GetHeight();

	float fw = w / 1280.0f;
	float fh = h / 720.0f;

	float f = fw > fh ? fh : fw;

	w = f * 1280.0f;
	h = f * 720.0f;

	GUI_PreviewSFML->SetSize(_event.GetSize());

	GUI_PreviewSFML->setSize(sf::Vector2u(w, h));
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