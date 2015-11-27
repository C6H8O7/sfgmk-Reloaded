MyGUI::MyGUI(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: GUI_MainFrame(parent, id, title, pos, size, style)
{
	selectedGameObject = 0;
}

void MyGUI::GUI_PanelEditor_OnSize(wxSizeEvent& _event)
{
	int w = GUI_PanelEditor->GetSize().GetWidth();
	int h = GUI_PanelEditor->GetSize().GetHeight();

	GUI_EditorSFML->SetSize(_event.GetSize());

	GUI_EditorSFML->setSize(sf::Vector2u(w, h));
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

void MyGUI::Update_PropertyGrid()
{
	if (!selectedGameObject)
		return;

	GUI_PropGameObjectName->SetValue(wxVariant(selectedGameObject->name.c_str()));

	GUI_PropTransformPosX->SetValue(wxVariant(selectedGameObject->transform.position.x));
	GUI_PropTransformPosY->SetValue(wxVariant(selectedGameObject->transform.position.y));
	GUI_PropTransformScaleX->SetValue(wxVariant(selectedGameObject->transform.scale.x));
	GUI_PropTransformScaleY->SetValue(wxVariant(selectedGameObject->transform.scale.y));
	GUI_PropTransformRotation->SetValue(wxVariant(selectedGameObject->transform.rotation));

	selectedGameObject->updateComponents();
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

		Update_PropertyGrid();
	}
}

void MyGUI::GUI_HierarchyTree_OnTreeSelChanged(wxTreeEvent& _event)
{
	if (selectedGameObject)
		selectedGameObject->showComponents(false);

	selectedGameObject = GameObjectManager::GetSingleton()->findGameObjectByTreeID(_event.GetItem().GetID());

	if (!selectedGameObject)
		return;

	printf("%s (%f; %f)\n", selectedGameObject->name.c_str(), selectedGameObject->transform.position.x, selectedGameObject->transform.position.y);

	selectedGameObject->showComponents(true);

	Update_PropertyGrid();
}

void MyGUI::GUI_MenuGameObjectCreateEmpty_OnMenuSelection(wxCommandEvent& _event)
{
	printf("adding gameobject\n");

	GameObjectManager::GetSingleton()->addGameObject(new GameObject());

	Update_HierarchyTree();
}

void MyGUI::GUI_PropertyGrid_OnPropertyGridChanged(wxPropertyGridEvent& _event)
{
	wxPGProperty* prop = _event.GetProperty();

	std::string category_name = std::string((const char*)prop->GetParent()->GetLabel().c_str());
	std::string property_name = std::string((const char*)prop->GetLabel());

	if (!selectedGameObject)
		return;

	if (category_name == "GameObject")
	{
		if (property_name == "Name")
			selectedGameObject->name = std::string((const char*)prop->GetValueAsString().c_str());

		Update_HierarchyTree();
	}

	if (category_name == "Transform")
	{
		float f = (float)prop->GetValue().GetDouble();

		if (property_name == "Pos X")
			selectedGameObject->transform.position.x = f;
		else if (property_name == "Pos Y")
			selectedGameObject->transform.position.y = f;
		else if (property_name == "Scale X")
			selectedGameObject->transform.scale.x = f;
		else if (property_name == "Scale Y")
			selectedGameObject->transform.scale.y = f;
		else if (property_name == "Rotation")
			selectedGameObject->transform.rotation = f;
	}

	sfgmk::vector<GameObjectComponent*>& components = selectedGameObject->getComponents();

	for (unsigned int i = 0; i < components.getElementNumber(); i++)
		components[i]->OnPropertyGridChanged(_event);
}

MyGUI* MyGUI::gui = 0;

void MyGUI::SetGUI(MyGUI* _gui)
{
	MyGUI::gui = _gui;
}

MyGUI* MyGUI::GetGUI()
{
	return MyGUI::gui;
}