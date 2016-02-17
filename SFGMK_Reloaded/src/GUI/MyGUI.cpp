#include "stdafx.h"

#ifdef SFGMKR_EDITOR

////////////////////////////////////////////////////////////////////////////////////////////////////// Constructor

MyGUI::MyGUI(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: GUI_MainFrame(parent, id, title, pos, size, style)
{
	selectedGameObject = 0;
	selectedGameObjectComponent = 0;

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

	GUI_PropertyGrid->Connect(wxEVT_PG_SELECTED, wxPropertyGridEventHandler(MyGUI::GUI_PropertyGrid_OnPropertyGridSelected), NULL, this);

	GUI_AssetsDirCtrl->Connect(wxEVT_DIRCTRL_FILEACTIVATED, wxTreeEventHandler(MyGUI::GUI_AssetsDirCtrl_OnFileActivation), NULL, this);

	/////////////////////////////////////////////////////////////////////////////// LUA

	ScriptEditor::GetSingleton()->init(&m_mgr, GUI_PanelScript, GUI_ScriptEditor, GUI_ScriptSelSpin, GUI_ScriptSelNum, GUI_ScriptSelName);

	GUI_ScriptEditor->Connect(wxEVT_STC_CHARADDED, wxStyledTextEventHandler(MyGUI::GUI_ScriptEditor_OnCharAdded), NULL, this);

	SFMLCanvas::project = new Project();

	/////////////////////////////////////////////////////////////////////////////// Components

	addComponentPath("Render");
	addComponentPath("IA");
	addComponentPath("IA/Steering");
	addComponentPath("IA/Steering/Behavior");
	addComponentPath("Physic");
	addComponentPath("Debug");
	addComponentPath("Audio");
	addComponentPath("Shape");

	addComponent("Render/Sprite", "Sprite");
	addComponent("Render/Camera", "Camera");
	addComponent("Render/Text", "Text");

	addComponent("IA/NeuronalNetwork", "NeuronalNetwork");

	addComponent("IA/Pathfinding Map", "PathfindingMap");
	addComponent("IA/Pathfinding Agent", "PathfindingAgent");
	addComponent("IA/Steering/Agent", "SteeringAgent");
	addComponent("IA/Steering/Formation", "SteeringFormation");
	addComponent("IA/Steering/Behavior/Seek", "SteeringSeek");
	addComponent("IA/Steering/Behavior/Flee", "SteeringFlee");
	addComponent("IA/Steering/Behavior/Pursuit", "SteeringPursuit");
	addComponent("IA/Steering/Behavior/Evasion", "SteeringEvasion");
	addComponent("IA/Steering/Behavior/Arrival", "SteeringArrival");
	addComponent("IA/Steering/Behavior/Obstacle Avoidance", "SteeringObstacleAvoidance");
	addComponent("IA/Steering/Behavior/Wander", "SteeringWander");
	addComponent("IA/Steering/Behavior/Lead Following", "SteeringLeadFollowing");
	addComponent("IA/Steering/Behavior/Separation", "SteeringSeparation");
	addComponent("IA/Steering/Behavior/Cohesion", "SteeringCohesion");
	addComponent("IA/Steering/Behavior/Alignment", "SteeringAlignment");
	addComponent("IA/Steering/Behavior/PathFollowing", "SteeringPathFollowing");
	addComponent("IA/Steering/Behavior/Formation Agent", "SteeringFormationAgent");

	addComponent("Physic/Sphere Collider", "Collider");
	addComponent("Physic/OBB Collider", "Collider");
	addComponent("Physic/Rigidbody", "Rigidbody");

	addComponent("Debug/Selector", "Selector");

	addComponent("Audio/Listener", "Listener");
	addComponent("Audio/SoundBuffer", "SoundBuffer");

	addComponent("Script", "Script");
	addComponent("Particle System", "ParticleSystem");
	addComponent("Tiled Map", "TiledMap");
	addComponent("Shape/Polygon", "Polygon");
	addComponent("Shape/ShapeContainer", "ShapeContainer");

	/////////////////////////////////////////////////////////////////////////////// Keys

	//Bind(wxEVT_CHAR_HOOK, &MyGUI::GUI_MainFrame_OnKeyDown, this); // Bloque toutes les entrees -_-
}

MyGUI::~MyGUI()
{
	GUI_HierarchyTree->Disconnect(wxEVT_TREE_ITEM_MENU, wxTreeEventHandler(MyGUI::GUI_HierarchyTreeOnContextMenu), NULL, this);
	GUI_AssetsDirCtrl->Disconnect(wxEVT_TREE_ITEM_MENU, wxTreeEventHandler(MyGUI::GUI_AssetsDirCtrlOnContextMenu), NULL, this);

	GUI_PropertyGrid->Disconnect(wxEVT_PG_SELECTED, wxPropertyGridEventHandler(MyGUI::GUI_PropertyGrid_OnPropertyGridSelected), NULL, this);

	GUI_AssetsDirCtrl->Disconnect(wxEVT_DIRCTRL_FILEACTIVATED, wxTreeEventHandler(MyGUI::GUI_AssetsDirCtrl_OnFileActivation), NULL, this);

	GUI_ScriptEditor->Disconnect(wxEVT_STC_CHARADDED, wxStyledTextEventHandler(MyGUI::GUI_ScriptEditor_OnCharAdded), NULL, this);

	cleanComponents();

	//Unbind(wxEVT_CHAR_HOOK, &MyGUI::GUI_MainFrame_OnKeyDown, this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Keys

r_void MyGUI::GUI_MainFrame_OnKeyDown(wxKeyEvent& _event)
{
	if (_event.ControlDown() && _event.GetKeyCode() != WXK_CONTROL)
	{
		if (SFGMKR_MYGUI_DEBUG)
			printf("[INFO] MyGUI : Ctrl + %d\n", _event.GetKeyCode());
	}
	else if (_event.AltDown() && _event.GetKeyCode() != WXK_ALT)
	{
		if (SFGMKR_MYGUI_DEBUG)
			printf("[INFO] MyGUI : Alt + %d\n", _event.GetKeyCode());
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Update PropertyGrid & HierarchyTree

r_void MyGUI::Empty_PropertyGrid()
{
	selectedGameObjectComponent = 0;

	gmk::vector<GameObject*>& gameobjects = SFMLCanvas::project->getCurrentScene()->getGameObjects();

	for (r_uint32 i = 0; i < gameobjects.size(); i++)
		gameobjects[i]->showComponents(false);
}

r_void MyGUI::Update_PropertyGrid()
{
	if (selectedGameObject)
		selectedGameObject->updateComponents();
}

r_void MyGUI::Update_HierarchyTree()
{
	GUI_HierarchyTree->Freeze();

	GUI_HierarchyTree->DeleteAllItems();
	GUI_HierarchyTree->ClearBackground();

	wxTreeItemId treeid = GUI_HierarchyTree->AddRoot("Scene");

	gmk::vector<GameObject*>& gameobjects = SFMLCanvas::project->getCurrentScene()->getGameObjects();

	for (r_uint32 i = 0; i < gameobjects.size(); i++)
	{
		GameObject* gameobject = gameobjects[i];

		gameobject->treeID = GUI_HierarchyTree->AppendItem(treeid, gameobject->name).GetID();
	}

	GUI_HierarchyTree->Thaw();
}

r_void MyGUI::AddTo_HierarchyTree(GameObject* _gameobject)
{
	_gameobject->treeID = GUI_HierarchyTree->AppendItem(GUI_HierarchyTree->GetRootItem().GetID(), _gameobject->name).GetID();
}

r_void MyGUI::RemoveFrom_HierarchyTree(GameObject* _gameobject)
{
	GUI_HierarchyTree->Delete(_gameobject->treeID);
}

////////////////////////////////////////////////////////////////////////////////////////////////////// OnSize des deux panels

r_void MyGUI::GUI_PanelEditor_OnSize(wxSizeEvent& _event)
{
	wxSize size = _event.GetSize();
	r_int32 w = size.x - 2, h = size.y - 2;

	GUI_EditorSFML->window.setSize(sf::Vector2u(w, h));
	GUI_EditorSFML->window.setPosition(r_vector2i(1, 1));

	sf::View view = GUI_EditorSFML->getView();
	view.setSize(r_vector2f((r_float)w, (r_float)h));

	GUI_EditorSFML->setView(view);
}

r_void MyGUI::GUI_PanelPreview_OnSize(wxSizeEvent& _event)
{
	r_int32 w = _event.GetSize().x;
	r_int32 h = _event.GetSize().y;

	r_float fw = w / SFGMKR_DEFAULT_SFML_SIZE_X;
	r_float fh = h / SFGMKR_DEFAULT_SFML_SIZE_Y;

	r_float f = fw > fh ? fh : fw;

	r_float nw = f * SFGMKR_DEFAULT_SFML_SIZE_X;
	r_float nh = f * SFGMKR_DEFAULT_SFML_SIZE_Y;

	GUI_PreviewSFML->window.setSize(sf::Vector2u(nw, nh));
	GUI_PreviewSFML->window.setPosition(r_vector2i(0.5f * (w - nw), 0.5f * (h - nh)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Events HierarchyTree

r_void MyGUI::GUI_HierarchyTree_OnTreeSelChanged(wxTreeEvent& _event)
{
	if (selectedGameObject)
		selectedGameObject->showComponents(false);

	selectedGameObject = SFMLCanvas::project->getCurrentScene()->findGameObjectByTreeID(_event.GetItem().GetID());

	if (SFGMKR_MYGUI_DEBUG)
		printf("[INFO] MyGUI : Selected object 0x%X\n", (r_uint32)selectedGameObject);

	if (!selectedGameObject)
		return;

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_HierarchyTreeMenuRemove_OnMenuSelection(wxCommandEvent& _event)
{
	if (selectedGameObject)
		SFMLCanvas::project->getCurrentScene()->removeGameObject(selectedGameObject);
}

r_void MyGUI::GUI_HierarchyTreeMenuMoveUp_OnMenuSelection(wxCommandEvent& _event)
{
	if (selectedGameObject)
	{
		gmk::vector<GameObject*>& gameobjects = SFMLCanvas::project->getCurrentScene()->getGameObjects();

		r_int32 index = gameobjects.findElementIndex(selectedGameObject);

		if (index > 0)
		{
			gameobjects.swapIndex(index - 1, index);

			Update_HierarchyTree();
		}
	}
}

r_void MyGUI::GUI_HierarchyTreeMenuMoveDown_OnMenuSelection(wxCommandEvent& _event)
{
	if (selectedGameObject)
	{
		gmk::vector<GameObject*>& gameobjects = SFMLCanvas::project->getCurrentScene()->getGameObjects();

		r_int32 index = gameobjects.findElementIndex(selectedGameObject);

		if (index < (r_int32)(gameobjects.size() - 1))
		{
			gameobjects.swapIndex(index, index + 1);

			Update_HierarchyTree();
		}
	}
}

r_void MyGUI::GUI_HierarchyTreeMenuDuplicate_OnMenuSelection(wxCommandEvent& _event)
{
	if( selectedGameObject )
		SFMLCanvas::project->getCurrentScene()->addGameObject(gmk::Factory::getSingleton()->duplicate(selectedGameObject));
}

r_void MyGUI::GUI_HierarchyTreeOnContextMenu(wxTreeEvent &_event)
{
	GUI_HierarchyTree->SetFocusedItem(_event.GetItem());

	GUI_HierarchyTree_OnTreeSelChanged(_event);

	PopupMenu(GUI_HierarchyTreeMenu);
}

r_void MyGUI::GUI_HierarchyTree_OnTreeItemActivated(wxTreeEvent& _event)
{
	if (selectedGameObject)
	{
		sf::View view = SFMLCanvas::editorCanvas->getView();

		view.setCenter(selectedGameObject->getCenter());

		SFMLCanvas::editorCanvas->setView(view);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Event AssetsDirCtrl

r_void MyGUI::GUI_AssetsRefresh_OnButtonClick(wxCommandEvent& _event)
{
	GUI_AssetsDirCtrl->ReCreateTree();
}

r_void MyGUI::GUI_AssetsOpen_OnButtonClick(wxCommandEvent& _event)
{
	wxFileName path(SFMLCanvas::project->getPath());
	path.MakeAbsolute();

	Project::OpenFolder((r_string)path.GetFullPath().c_str());
}

r_void MyGUI::GUI_AssetsDirCtrl_OnBeginDrag(wxTreeEvent& _event)
{
	wxString text = GUI_AssetsDirCtrl->GetPath(_event.GetItem());

	wxTextDataObject object(text);

	wxDropSource source(object, GUI_AssetsDirCtrl);

	source.DoDragDrop(wxDrag_CopyOnly);
}

r_void MyGUI::GUI_AssetsDirCtrlMenuAdd_OnMenuSelection(wxCommandEvent& _event)
{
	r_string filePath = r_string(GUI_AssetsDirCtrl->GetFilePath().c_str());
	std::replace(filePath.begin(), filePath.end(), '\\', '/');

	if (!selectedGameObject)
		return;

	GameObject::AddAsComponent(selectedGameObject, filePath);
}

r_void MyGUI::GUI_AssetsDirCtrlOnContextMenu(wxTreeEvent &_event)
{
	wxTreeCtrl* treectrl = GUI_AssetsDirCtrl->GetTreeCtrl();

	treectrl->SetFocusedItem(_event.GetItem());

	PopupMenu(GUI_AssetsDirCtrlMenu);
}

r_void MyGUI::GUI_AssetsDirCtrl_OnFileActivation(wxTreeEvent& _event)
{
	r_string filePath = r_string(GUI_AssetsDirCtrl->GetFilePath().c_str());
	std::replace(filePath.begin(), filePath.end(), '\\', '/');

	if (filePath.find(".gmkscene") != r_string::npos)
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(filePath.c_str());
		Project::LoadSceneByName(doc.FirstChildElement("Scene")->Attribute("name"));
	}
	if (filePath.find(".lua") != r_string::npos)
	{
		ScriptEditor::GetSingleton()->open(filePath);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Menu GameObject

r_void MyGUI::GUI_MenuGameObjectCreateEmpty_OnMenuSelection(wxCommandEvent& _event)
{
	GameObject* gameobject = new GameObject();

	SFMLCanvas::project->getCurrentScene()->addGameObject(gameobject);

	if (selectedGameObject)
		selectedGameObject->showComponents(false);

	selectedGameObject = gameobject;

	if (SFGMKR_MYGUI_DEBUG)
		printf("[INFO] MyGUI : Selected object 0x%X\n", (r_uint32)selectedGameObject);

	selectedGameObject->showComponents(true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Events PropertyGrid

r_void MyGUI::GUI_PropertyRefresh_OnButtonClick(wxCommandEvent& _event)
{
	Update_PropertyGrid();
}

r_void MyGUI::GUI_PropertyGrid_OnPropertyGridChanged(wxPropertyGridEvent& _event)
{
	gmk::vector<GameObjectComponent*>& components = selectedGameObject->getComponents();

	for (r_uint32 i = 0; i < components.size(); i++)
		components[i]->OnPropertyGridChanged(_event);
}

r_void MyGUI::GUI_PropertyGrid_OnPropertyGridSelected(wxPropertyGridEvent& _event)
{
	gmk::vector<GameObjectComponent*>& components = selectedGameObject->getComponents();

	for (r_uint32 i = 0; i < components.size(); i++)
	{
		GameObjectComponent* component = components[i];

		gmk::vector<GameObjectComponent::ComponentProperty*>& properties = component->m_Properties;

		for (r_uint32 j = 0; j < properties.size(); j++)
			if (properties[j]->wxProperty == _event.GetProperty())
				selectedGameObjectComponent = component;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Events ProjectGrid

r_void MyGUI::GUI_ProjectProperty_OnPropertyGridChanged(wxPropertyGridEvent& _event)
{
	wxPGProperty* prop = _event.GetProperty();
	
	r_string name = r_string((const r_int8*)prop->GetName().c_str());
	wxVariant value = prop->GetValue();

	Project* project = SFMLCanvas::project;

	if (name == "Name")
		project->setName((const r_int8*)value.GetString().c_str());
	else if (name == "Path")
	{
		project->setPath((const r_int8*)value.GetString().c_str());

		GUI_AssetsDirCtrl->SetRoot(project->getPath());
		GUI_AssetsDirCtrl->ReCreateTree();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Menu File

r_void MyGUI::GUI_MenuFileNew_OnMenuSelection(wxCommandEvent& _event)
{
	wxMessageDialog dialog(this, "Do you wish to create a new scene ?", "Warning", wxYES_NO | wxICON_WARNING);

	if (dialog.ShowModal() == wxID_YES)
	{
		selectedGameObject = 0;

		SFMLCanvas::project->getCurrentScene()->removeGameObjects();

		Update_HierarchyTree();
	}
}

r_void MyGUI::GUI_MenuFileOpen_OnMenuSelection(wxCommandEvent& _event)
{
	Project* project = SFMLCanvas::project;

	if (project->getPath().size())
		project->getCurrentScene()->load();
}

r_void MyGUI::GUI_MenuFileSave_OnMenuSelection(wxCommandEvent& _event)
{
	Project* project = SFMLCanvas::project;

	if (project->getPath().size())
		project->getCurrentScene()->save();
}

r_void MyGUI::GUI_MenuFileOpenProject_OnMenuSelection(wxCommandEvent& _event)
{
	wxFileDialog openProjectDialog(this, "Open GMK Project file", "", "", "GMK Project file (*.gmkproject)|*.gmkproject", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openProjectDialog.ShowModal() == wxID_CANCEL)
		return;

	r_string projectPath = r_string((const r_int8*)openProjectDialog.GetPath().c_str());

	if(SFGMKR_MYGUI_DEBUG)
		std::cout << "[INFO] MyGUI : Opening " << projectPath << std::endl;

	Project* project = SFMLCanvas::project;

	project->load(projectPath.c_str());

	r_string path = project->getPath();
	
	if (path.size())
	{
		Project::CreateFolder(project->getAssetsPath());
		Project::CreateFolder(project->getScenesPath());
		Project::CreateFolder(project->getPrefabsPath());
	}

	GUI_AssetsDirCtrl->SetRoot(SFMLCanvas::project->getPath());
	GUI_AssetsDirCtrl->ReCreateTree();
}

r_void MyGUI::GUI_MenuFileSaveProject_OnMenuSelection(wxCommandEvent& _event)
{
	wxFileDialog saveProjectDialog(this, "Save GMK Project file", "", "", "GMK Project file (*.gmkproject)|*.gmkproject", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveProjectDialog.ShowModal() == wxID_CANCEL)
		return;

	r_string projectPath = r_string((const r_int8*)saveProjectDialog.GetPath().c_str());

	if (SFGMKR_MYGUI_DEBUG)
		std::cout << "[INFO] MyGUI : Saving " << projectPath << std::endl;

	Project* project = SFMLCanvas::project;

	project->save(projectPath.c_str());

	r_string path = project->getPath();

	if (path.size())
	{
		Project::CreateFolder(project->getAssetsPath());
		Project::CreateFolder(project->getScenesPath());
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Menu View

r_void MyGUI::GUI_MenuViewProject_OnMenuSelection(wxCommandEvent& _event)
{
	wxAuiPaneInfo& pane = m_mgr.GetPane(GUI_PanelProject);

	if (pane.IsShown())
		pane.Hide();
	else
		pane.Show();

	m_mgr.Update();
}

r_void MyGUI::GUI_MenuViewScriptEditor_OnMenuSelection(wxCommandEvent& _event)
{
	ScriptEditor::GetSingleton()->toggleView();
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Menu Game

r_void MyGUI::GUI_MenuGamePlay_OnMenuSelection(wxCommandEvent& _event)
{
	if (!SFMLCanvas::isPlaying)
	{
		SFMLCanvas::isPlaying = true;
		gmk::TimeManager::GetSingleton()->setFactor(1.0f);
		gmk::TimeManager::GetSingleton()->resetDeltaTime();

		SFMLCanvas::project->getCurrentScene()->saveTemp("../data/editor/temp.gmkscene");
	}
}

r_void MyGUI::GUI_MenuGameStop_OnMenuSelection(wxCommandEvent& _event)
{
	if (SFMLCanvas::isPlaying)
	{
		SFMLCanvas::isPlaying = false;
		gmk::TimeManager::GetSingleton()->setFactor(0.0f);

		SFMLCanvas::project->getCurrentScene()->loadTemp("../data/editor/temp.gmkscene");
	}
}

r_void MyGUI::GUI_MenuGamePause_OnMenuSelection(wxCommandEvent& _event)
{
	if (SFMLCanvas::isPlaying)
	{
		SFMLCanvas::isPlaying = false;
		gmk::TimeManager::GetSingleton()->setFactor(0.0f);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Script Editor

r_void MyGUI::GUI_ScriptEditor_OnCharAdded(wxStyledTextEvent &_event)
{
	ScriptEditor::GetSingleton()->charAdded(_event);
}

r_void MyGUI::GUI_ScriptSelSpin_OnSpin(wxSpinEvent& _event)
{
	ScriptEditor::GetSingleton()->spin(_event);
}

r_void MyGUI::GUI_ScriptSave_OnButtonClick(wxCommandEvent& _event)
{
	ScriptEditor::GetSingleton()->save(_event);
}

r_void MyGUI::GUI_ScriptClose_OnButtonClick(wxCommandEvent& _event)
{
	ScriptEditor::GetSingleton()->close(_event);
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Components

r_void MyGUI::addComponentPath(r_string _path)
{
	std::vector<r_string> dirs = gmk::stringSplit(_path, '/');

	if (dirs.size())
	{
		sGUI_COMPONENT* component = new sGUI_COMPONENT();
		component->isPath = true;
		component->path = _path;
		component->name = dirs[dirs.size() - 1];
		component->type = "";

		if (dirs.size() > 1)
		{
			r_string path = _path.substr(0, _path.find_last_of('/'));

			for (r_uint32 i = 0; i < m_GUIComponents.size(); i++)
			{
				sGUI_COMPONENT* parent = m_GUIComponents[i];

				if (parent->path == path)
				{
					component->menu = new wxMenu();
					component->item = new wxMenuItem(GUI_MenuComponent, wxID_ANY, component->name, wxEmptyString, wxITEM_NORMAL, component->menu);
					parent->menu->Append(component->item);
				}
			}
		}
		else
		{
			component->menu = new wxMenu();
			component->item = new wxMenuItem(GUI_MenuComponent, wxID_ANY, component->name, wxEmptyString, wxITEM_NORMAL, component->menu);
			GUI_MenuComponent->Append(component->item);
		}

		m_GUIComponents.push_back(component);
	}
}

r_void MyGUI::addComponent(r_string _path, r_string _type)
{
	if (_type.size())
	{
		std::vector<r_string> dirs = gmk::stringSplit(_path, '/');

		sGUI_COMPONENT* component = new sGUI_COMPONENT();
		component->isPath = false;
		component->path = _path;
		component->name = dirs[dirs.size() - 1];
		component->type = _type;
		component->menu = 0;
		component->userData = new wxVariant(wxString(component->type));

		if (dirs.size() > 1)
		{
			for (r_uint32 i = 0; i < m_GUIComponents.size(); i++)
			{
				sGUI_COMPONENT* parent = m_GUIComponents[i];

				if (parent->path == _path.substr(0, _path.find_last_of('/')))
				{
					component->item = new wxMenuItem(GUI_MenuComponent, wxID_ANY, component->name, wxEmptyString, wxITEM_NORMAL);
					parent->menu->Append(component->item);
					this->Connect(component->item->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyGUI::GUI_MenuComponentItem_OnMenuSelection), component->userData, this);
				}
			}
		}
		else
		{
			component->item = new wxMenuItem(GUI_MenuComponent, wxID_ANY, component->name, wxEmptyString, wxITEM_NORMAL);
			GUI_MenuComponent->Append(component->item);
			this->Connect(component->item->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyGUI::GUI_MenuComponentItem_OnMenuSelection), component->userData, this);
		}

		m_GUIComponents.push_back(component);
	}
}

r_void MyGUI::createAndAddComponent(r_string _name)
{
	if (!selectedGameObject)
		return;

	GameObjectComponent* component = ComponentsBank::GetSingleton()->createComponent(_name, selectedGameObject);

	selectedGameObject->addComponent(component);

	selectedGameObject->showComponents(true);
}

r_void MyGUI::cleanComponents()
{
	for (r_uint32 i = 0; i < m_GUIComponents.size(); i++)
	{
		sGUI_COMPONENT* component = m_GUIComponents[i];

		if (!component->menu)
			this->Disconnect(component->item->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyGUI::GUI_MenuComponentItem_OnMenuSelection), component->userData, this);
	}

	m_GUIComponents.deleteAndClear();
}

r_void MyGUI::GUI_MenuComponentItem_OnMenuSelection(wxCommandEvent& _event)
{
	wxVariant* userData = (wxVariant*)_event.GetEventUserData();

	r_string type = (const char*)userData->GetString().c_str();

	createAndAddComponent(type);
}

////////////////////////////////////////////////////////////////////////////////////////////////////// MyGUI

MyGUI* MyGUI::gui = 0;

r_void MyGUI::SetGUI(MyGUI* _gui)
{
	MyGUI::gui = _gui;
}

MyGUI* MyGUI::GetGUI()
{
	return MyGUI::gui;
}

#endif