#ifdef SFGMKR_EDITOR

////////////////////////////////////////////////////////////////////////////////////////////////////// Constructor

MyGUI::MyGUI(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: GUI_MainFrame(parent, id, title, pos, size, style)
{
	selectedGameObject = 0;

	GUI_AssetsDirCtrl->SetDefaultPath(wxGetCwd());
	GUI_AssetsDirCtrl->ReCreateTree();

	wxIdleEvent::SetMode(wxIDLE_PROCESS_SPECIFIED);

	wxMyTextDropTargetProperties* targetProperties = new wxMyTextDropTargetProperties(GUI_PropertyGrid);
	GUI_PropertyGrid->SetDropTarget(targetProperties);

	wxMyTextDropTargetEditor* targetEditor = new wxMyTextDropTargetEditor(GUI_EditorSFML);
	GUI_EditorSFML->SetDropTarget(targetEditor);

	GUI_HierarchyTree->Disconnect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(GUI_MainFrame::GUI_HierarchyTreeOnContextMenu), NULL, this);
	GUI_AssetsDirCtrl->Disconnect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(GUI_MainFrame::GUI_AssetsDirCtrlOnContextMenu), NULL, this);

	GUI_HierarchyTree->Connect(wxEVT_TREE_ITEM_MENU, wxTreeEventHandler(MyGUI::GUI_HierarchyTreeOnContextMenu), NULL, this);
	GUI_AssetsDirCtrl->Connect(wxEVT_TREE_ITEM_MENU, wxTreeEventHandler(MyGUI::GUI_AssetsDirCtrlOnContextMenu), NULL, this);
}

MyGUI::~MyGUI()
{
	GUI_HierarchyTree->Disconnect(wxEVT_TREE_ITEM_MENU, wxTreeEventHandler(MyGUI::GUI_HierarchyTreeOnContextMenu), NULL, this);
	GUI_AssetsDirCtrl->Disconnect(wxEVT_TREE_ITEM_MENU, wxTreeEventHandler(MyGUI::GUI_AssetsDirCtrlOnContextMenu), NULL, this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Update PropertyGrid & HierarchyTree

void MyGUI::Update_PropertyGrid()
{
	if (selectedGameObject)
	{
		GUI_PropGameObjectName->SetValue(wxVariant(selectedGameObject->name.c_str()));

		GUI_PropTransformPosX->SetValue(wxVariant(selectedGameObject->transform.position.x));
		GUI_PropTransformPosY->SetValue(wxVariant(selectedGameObject->transform.position.y));
		GUI_PropTransformScaleX->SetValue(wxVariant(selectedGameObject->transform.scale.x));
		GUI_PropTransformScaleY->SetValue(wxVariant(selectedGameObject->transform.scale.y));
		GUI_PropTransformRotation->SetValue(wxVariant(selectedGameObject->transform.rotation));

		selectedGameObject->updateComponents();
	}
	else
	{
		GUI_PropGameObjectName->SetValue(wxVariant(""));

		GUI_PropTransformPosX->SetValue(wxVariant(0.0f));
		GUI_PropTransformPosY->SetValue(wxVariant(0.0f));
		GUI_PropTransformScaleX->SetValue(wxVariant(1.0f));
		GUI_PropTransformScaleY->SetValue(wxVariant(1.0f));
		GUI_PropTransformRotation->SetValue(wxVariant(0.0f));
	}
}

void MyGUI::Update_HierarchyTree()
{
	GUI_HierarchyTree->DeleteAllItems(); // On le fait deux fois, juste au cas ou
	GUI_HierarchyTree->DeleteAllItems();

	wxTreeItemId treeid = GUI_HierarchyTree->AddRoot("Scene");

	sfgmk::vector<GameObject*>& gameobjects = GameObjectManager::GetSingleton()->getGameObjects();

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
	{
		GameObject* gameobject = gameobjects[i];

		gameobject->treeID = GUI_HierarchyTree->AppendItem(treeid, gameobject->name).GetID();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////// OnSize des deux panels

void MyGUI::GUI_PanelEditor_OnSize(wxSizeEvent& _event)
{
	int w = GUI_PanelEditor->GetSize().GetWidth();
	int h = GUI_PanelEditor->GetSize().GetHeight();

	GUI_EditorSFML->SetSize(_event.GetSize());

	GUI_EditorSFML->setSize(sf::Vector2u(w, h));

	GUI_EditorSFML->m_DefaultWidth = (float)w;
	GUI_EditorSFML->m_DefaultHeight = (float)h;
	GUI_EditorSFML->m_Zoom = 1.0f;

	sf::View view;
	view.setSize(sf::Vector2f((float)w, (float)h));
	view.setCenter(GUI_EditorSFML->getView().getCenter());

	GUI_EditorSFML->setView(view);
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

////////////////////////////////////////////////////////////////////////////////////////////////////// Events HierarchyTree

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

	selectedGameObject->showComponents(true);

	Update_PropertyGrid();
}

void MyGUI::GUI_HierarchyTreeMenuRemove_OnMenuSelection(wxCommandEvent& _event)
{
	if (selectedGameObject)
	{
		selectedGameObject->showComponents(false);

		GameObjectManager::GetSingleton()->removeGameObject(selectedGameObject);

		selectedGameObject = 0;

		Update_HierarchyTree();

		Update_PropertyGrid();
	}
}

void MyGUI::GUI_HierarchyTreeMenuMoveUp_OnMenuSelection(wxCommandEvent& _event)
{
	if (selectedGameObject)
	{
		sfgmk::vector<GameObject*>& gameobjects = GameObjectManager::GetSingleton()->getGameObjects();

		int index = gameobjects.findElementIndex(selectedGameObject);

		if (index > 0)
		{
			gameobjects.swapIndex(index - 1, index);

			Update_HierarchyTree();
		}
	}
}

void MyGUI::GUI_HierarchyTreeMenuMoveDown_OnMenuSelection(wxCommandEvent& _event)
{
	if (selectedGameObject)
	{
		sfgmk::vector<GameObject*>& gameobjects = GameObjectManager::GetSingleton()->getGameObjects();

		int index = gameobjects.findElementIndex(selectedGameObject);

		if (index < (int)(gameobjects.getElementNumber() - 1))
		{
			gameobjects.swapIndex(index, index + 1);

			Update_HierarchyTree();
		}
	}
}

void MyGUI::GUI_HierarchyTreeOnContextMenu(wxTreeEvent &_event)
{
	GUI_HierarchyTree->SetFocusedItem(_event.GetItem());

	GUI_HierarchyTree_OnTreeSelChanged(_event);

	PopupMenu(GUI_HierarchyTreeMenu);
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Event AssetsDirCtrl

void MyGUI::GUI_AssetsRefresh_OnButtonClick(wxCommandEvent& _event)
{
	GUI_AssetsDirCtrl->ReCreateTree();
}

void MyGUI::GUI_AssetsOpen_OnButtonClick(wxCommandEvent& _event)
{
	char command[MAX_PATH];
	sprintf_s(command, "explorer %s", Scene::GetDataPath().c_str());
	system(command);
}

void MyGUI::GUI_AssetsDirCtrl_OnBeginDrag(wxTreeEvent& _event)
{
	wxString text = GUI_AssetsDirCtrl->GetPath(_event.GetItem());

	wxTextDataObject object(text);

	wxDropSource source(object, GUI_AssetsDirCtrl);

	source.DoDragDrop(wxDrag_CopyOnly);
}

void MyGUI::GUI_AssetsDirCtrlMenuAdd_OnMenuSelection(wxCommandEvent& _event)
{
	std::string filePath = std::string(GUI_AssetsDirCtrl->GetFilePath().c_str());

	if (!selectedGameObject)
		return;

	GameObject::AddAsComponent(selectedGameObject, filePath);
}

void MyGUI::GUI_AssetsDirCtrlOnContextMenu(wxTreeEvent &_event)
{
	wxTreeCtrl* treectrl = GUI_AssetsDirCtrl->GetTreeCtrl();

	treectrl->SetFocusedItem(_event.GetItem());

	PopupMenu(GUI_AssetsDirCtrlMenu);
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Menu GameObject

void MyGUI::GUI_MenuGameObjectCreateEmpty_OnMenuSelection(wxCommandEvent& _event)
{
	GameObjectManager::GetSingleton()->addGameObject(new GameObject());

	Update_HierarchyTree();
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Events PropertyGrid

void MyGUI::GUI_PropertyRefresh_OnButtonClick(wxCommandEvent& _event)
{
	Update_PropertyGrid();
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

////////////////////////////////////////////////////////////////////////////////////////////////////// Menu Component

void MyGUI::GUI_MenuComponentSubRenderSprite_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentSprite(selectedGameObject));
}

void MyGUI::GUI_MenuComponentScript_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentScript(selectedGameObject));
}

void MyGUI::GUI_MenuComponentSubRenderCamera_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentCamera(selectedGameObject));
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Menu File

void MyGUI::GUI_MenuFileNew_OnMenuSelection(wxCommandEvent& _event)
{
	GameObjectManager::GetSingleton()->removeGameObjects();

	Update_HierarchyTree();
}

void MyGUI::GUI_MenuFileOpen_OnMenuSelection(wxCommandEvent& _event)
{
	Scene::Load(DEFAULT_SCENE_FILE);
}

void MyGUI::GUI_MenuFileSave_OnMenuSelection(wxCommandEvent& _event)
{
	Scene::Save(DEFAULT_SCENE_FILE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Menu Game

void MyGUI::GUI_MenuGamePlay_OnMenuSelection(wxCommandEvent& _event)
{
	if (!SFMLCanvas::isPlaying)
	{
		SFMLCanvas::isPlaying = true;
		sfgmk::TimeManager::GetSingleton()->setFactor(1.0f);
		Scene::Save(DEFAULT_TEMP_SCENE_FILE);
	}
}

void MyGUI::GUI_MenuGameStop_OnMenuSelection(wxCommandEvent& _event)
{
	if (SFMLCanvas::isPlaying)
	{
		SFMLCanvas::isPlaying = false;
		sfgmk::TimeManager::GetSingleton()->setFactor(0.0f);
		Scene::Load(DEFAULT_TEMP_SCENE_FILE);
	}
}

void MyGUI::GUI_MenuGamePause_OnMenuSelection(wxCommandEvent& _event)
{
	if (SFMLCanvas::isPlaying)
	{
		SFMLCanvas::isPlaying = false;
		sfgmk::TimeManager::GetSingleton()->setFactor(0.0f);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////// MyGUI

MyGUI* MyGUI::gui = 0;

void MyGUI::SetGUI(MyGUI* _gui)
{
	MyGUI::gui = _gui;
}

MyGUI* MyGUI::GetGUI()
{
	return MyGUI::gui;
}

#endif