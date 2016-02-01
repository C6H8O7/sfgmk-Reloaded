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

	GUI_ScriptEditor->SetLexer(wxSTC_LEX_CPP);

	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_DEFAULT, wxColor(255, 0, 0));

	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_COMMENT, wxColor(0, 128, 0));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_COMMENTLINE, wxColor(0, 128, 0));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_COMMENTDOC, wxColor(0, 128, 0));

	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_NUMBER, wxColor(255, 128, 0));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_STRING, wxColor(255, 0, 0));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_CHARACTER, wxColor(255, 0, 0));

	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_LITERALSTRING, wxColor(0, 255, 255));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_PREPROCESSOR, wxColor(0, 255, 255));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_IDENTIFIER, wxColor(0, 0, 0));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_STRINGEOL, wxColor(0, 255, 255));

	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_WORD2, wxColor(0, 255, 255));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_WORD3, wxColor(0, 255, 255));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_WORD4, wxColor(0, 255, 255));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_WORD5, wxColor(0, 255, 255));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_WORD6, wxColor(0, 255, 255));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_WORD7, wxColor(0, 255, 255));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_WORD8, wxColor(0, 255, 255));
	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_LABEL, wxColor(0, 255, 255));

	GUI_ScriptEditor->StyleSetForeground(wxSTC_LUA_WORD, wxColor(0, 0, 255));
	GUI_ScriptEditor->SetKeyWords(0, "if else then function end nil while for return");

	SFMLCanvas::project = new Project();
}

MyGUI::~MyGUI()
{
	GUI_HierarchyTree->Disconnect(wxEVT_TREE_ITEM_MENU, wxTreeEventHandler(MyGUI::GUI_HierarchyTreeOnContextMenu), NULL, this);
	GUI_AssetsDirCtrl->Disconnect(wxEVT_TREE_ITEM_MENU, wxTreeEventHandler(MyGUI::GUI_AssetsDirCtrlOnContextMenu), NULL, this);

	GUI_PropertyGrid->Disconnect(wxEVT_PG_SELECTED, wxPropertyGridEventHandler(MyGUI::GUI_PropertyGrid_OnPropertyGridSelected), NULL, this);

	GUI_AssetsDirCtrl->Disconnect(wxEVT_DIRCTRL_FILEACTIVATED, wxTreeEventHandler(MyGUI::GUI_AssetsDirCtrl_OnFileActivation), NULL, this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Update PropertyGrid & HierarchyTree

r_void MyGUI::Empty_PropertyGrid()
{
	selectedGameObjectComponent = 0;

	gmk::vector<GameObject*>& gameobjects = SFMLCanvas::project->getCurrentScene()->getGameObjects();

	for (r_uint32 i = 0; i < gameobjects.size(); i++)
	{
		gameobjects[i]->showComponents(false);
	}
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

////////////////////////////////////////////////////////////////////////////////////////////////////// OnSize des deux panels

r_void MyGUI::GUI_PanelEditor_OnSize(wxSizeEvent& _event)
{
	r_int32 w = GUI_PanelEditor->GetSize().GetWidth();
	r_int32 h = GUI_PanelEditor->GetSize().GetHeight();

	GUI_EditorSFML->SetSize(_event.GetSize());

	GUI_EditorSFML->setSize(sf::Vector2u(w, h));

	GUI_EditorSFML->m_DefaultWidth = (r_float)w;
	GUI_EditorSFML->m_DefaultHeight = (r_float)h;
	GUI_EditorSFML->m_Zoom = 1.0f;

	sf::View view;
	view.setSize(r_vector2f((r_float)w, (r_float)h));
	view.setCenter(GUI_EditorSFML->getView().getCenter());

	GUI_EditorSFML->setView(view);
}

r_void MyGUI::GUI_PanelPreview_OnSize(wxSizeEvent& _event)
{
	r_int32 w = GUI_PanelPreview->GetSize().GetWidth();
	r_int32 h = GUI_PanelPreview->GetSize().GetHeight();

	r_float fw = w / SFGMKR_DEFAULT_SFML_SIZE_X;
	r_float fh = h / SFGMKR_DEFAULT_SFML_SIZE_Y;

	r_float f = fw > fh ? fh : fw;

	r_float nw = f * SFGMKR_DEFAULT_SFML_SIZE_X;
	r_float nh = f * SFGMKR_DEFAULT_SFML_SIZE_Y;

	GUI_PreviewSFML->SetSize(_event.GetSize());

	GUI_PreviewSFML->setSize(sf::Vector2u(nw, nh));
	GUI_PreviewSFML->setPosition(r_vector2i(0.5f * (w - nw), 0.5f * (h - nh)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Events HierarchyTree

r_void MyGUI::GUI_HierarchyTree_OnTreeEndLabelEdit(wxTreeEvent& _event)
{
	GameObject* gameobject = SFMLCanvas::project->getCurrentScene()->findGameObjectByTreeID(_event.GetItem().GetID());

	if (gameobject)
	{
		gameobject->name = r_string(_event.GetLabel().c_str());

		Update_PropertyGrid();
	}
}

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
	{
		selectedGameObject->showComponents(false);

		SFMLCanvas::project->getCurrentScene()->removeGameObject(selectedGameObject);

		selectedGameObject = 0;

		Update_HierarchyTree();

		Update_PropertyGrid();
	}
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
	{
		//Sauvegarde en mémoire du modèle
		tinyxml2::XMLDocument Doc;
		tinyxml2::XMLElement* GameObject_elem = Doc.NewElement("GameObject");
		Doc.LinkEndChild(GameObject_elem);
		gmk::vector<GameObjectComponent*>& Components = selectedGameObject->getComponents();

		for( r_uint32 i(0); i < Components.size(); i++ )
		{
			GameObjectComponent* Component = Components[i];
			tinyxml2::XMLElement* Component_elem = Doc.NewElement("Component");
			GameObject_elem->LinkEndChild(Component_elem);
			Component_elem->SetAttribute("type", Component->type_name.c_str());
			Component->OnXMLSave(Component_elem);
		}

		//Création nouvel élément depuis modèle en mémoire
		GameObject* SelectedObjectCopy = new GameObject(false);

		GameObject_elem = Doc.FirstChildElement("GameObject");
		tinyxml2::XMLElement* Component_elem = GameObject_elem->FirstChildElement("Component");

		while( Component_elem )
		{
			GameObjectComponent* Component =  NULL;
			r_string type = Component_elem->Attribute("type");

			Component = ComponentsBank::GetSingleton()->createComponent(type, SelectedObjectCopy);

			if( Component )
			{
				Component->OnXMLLoad(Component_elem);
				Component->OnMembersUpdate();
				SelectedObjectCopy->addComponent(Component);
			}

			Component_elem = Component_elem->NextSiblingElement("Component");
		}

		SelectedObjectCopy->name += "cpy";

		//Ajout scène
		SFMLCanvas::project->getCurrentScene()->addGameObject(SelectedObjectCopy);
		Update_HierarchyTree();
		Update_PropertyGrid();
	}
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
	wxFileName path(SFMLCanvas::project->getAssetsPath());
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
		Project::LoadSceneByPath(filePath);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Menu GameObject

r_void MyGUI::GUI_MenuGameObjectCreateEmpty_OnMenuSelection(wxCommandEvent& _event)
{
	GameObject* gameobject = new GameObject();

	SFMLCanvas::project->getCurrentScene()->addGameObject(gameobject);

	gameobject->treeID = GUI_HierarchyTree->AppendItem(GUI_HierarchyTree->GetRootItem(), gameobject->name);

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

////////////////////////////////////////////////////////////////////////////////////////////////////// Menu Component

r_void MyGUI::GUI_MenuComponentSubRenderSprite_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentSprite(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentScript_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentScript(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentSubRenderCamera_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentCamera(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentParticleSystem_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentParticleSystem(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentTiledMap_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentTiledMap(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentSubIAPathfindingMap_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentPathfindingMap(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentSubIASubSteeringSubBehaviorSeek_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentSteeringSeek(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentSubIASubSteeringAgent_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentSteeringAgent(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentSubIAPathfindingAgent_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentPathfindingAgent(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentPolygon_OnMenuSelection(wxCommandEvent& _event)
{
	if( !selectedGameObject )
		return;

	selectedGameObject->addComponent(new ComponentPolygon(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentSubPhysicOBB_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	ComponentCollider* component = new ComponentCollider(selectedGameObject);
	component->initType(gmk::eCOLLIDER_TYPE::eOBB);

	selectedGameObject->addComponent(component);

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentSubPhysicSphere_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	ComponentCollider* component = new ComponentCollider(selectedGameObject);
	component->initType(gmk::eCOLLIDER_TYPE::eSphere);

	selectedGameObject->addComponent(component);

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentSubPhysicRigidbody_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentRigidbody(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentSubDebugSelector_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentSelector(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentSubRenderText_OnMenuSelection(wxCommandEvent& _event)
{
	if (!selectedGameObject)
		return;

	selectedGameObject->addComponent(new ComponentText(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentSubAudioListener_OnMenuSelection(wxCommandEvent& _event)
{
	if( !selectedGameObject )
		return;

	selectedGameObject->addComponent(new ComponentListener(selectedGameObject));

	selectedGameObject->showComponents(true);
}

r_void MyGUI::GUI_MenuComponentSubAudioSoundBuffer_OnMenuSelection(wxCommandEvent& _event)
{
	if( !selectedGameObject )
		return;

	selectedGameObject->addComponent(new ComponentSoundBuffer(selectedGameObject));

	selectedGameObject->showComponents(true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////// Menu File

r_void MyGUI::GUI_MenuFileNew_OnMenuSelection(wxCommandEvent& _event)
{
	selectedGameObject = 0;

	SFMLCanvas::project->getCurrentScene()->removeGameObjects();

	GUI_HierarchyTree->DeleteAllItems();
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

		gmk::Factory::getSingleton()->loadPrefabs("../../project/prefabs/PrefabList.prefabs");
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

		gmk::Factory::getSingleton()->savePrefabs("../../project/prefabs/PrefabList.prefabs");
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
	wxAuiPaneInfo& pane = m_mgr.GetPane(GUI_PanelScript);

	if (pane.IsShown())
		pane.Hide();
	else
		pane.Show();

	m_mgr.Update();
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