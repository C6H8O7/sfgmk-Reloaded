///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

GUI_MainFrame::GUI_MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	GUI_PanelHierarchy = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GUI_PanelHierarchy->SetScrollRate(5, 5);
	m_mgr.AddPane(GUI_PanelHierarchy, wxAuiPaneInfo().Right().Caption(wxT("Hierarchy")).CloseButton(false).Dock().Resizable().FloatingSize(wxSize(166, 59)).Row(2).MinSize(wxSize(150, 300)));

	wxBoxSizer* GUI_SizerHierarchy;
	GUI_SizerHierarchy = new wxBoxSizer(wxVERTICAL);

	GUI_HierarchyTree = new wxTreeCtrl(GUI_PanelHierarchy, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS | wxTR_HIDE_ROOT | wxTR_LINES_AT_ROOT);
	GUI_HierarchyTreeMenu = new wxMenu();
	wxMenuItem* GUI_HierarchyTreeMenuRemove;
	GUI_HierarchyTreeMenuRemove = new wxMenuItem(GUI_HierarchyTreeMenu, wxID_ANY, wxString(wxT("Remove")), wxEmptyString, wxITEM_NORMAL);
	GUI_HierarchyTreeMenu->Append(GUI_HierarchyTreeMenuRemove);

	wxMenuItem* GUI_HierarchyTreeMenuMoveUp;
	GUI_HierarchyTreeMenuMoveUp = new wxMenuItem(GUI_HierarchyTreeMenu, wxID_ANY, wxString(wxT("Move Up")), wxEmptyString, wxITEM_NORMAL);
	GUI_HierarchyTreeMenu->Append(GUI_HierarchyTreeMenuMoveUp);

	wxMenuItem* GUI_HierarchyTreeMenuMoveDown;
	GUI_HierarchyTreeMenuMoveDown = new wxMenuItem(GUI_HierarchyTreeMenu, wxID_ANY, wxString(wxT("Move Down")), wxEmptyString, wxITEM_NORMAL);
	GUI_HierarchyTreeMenu->Append(GUI_HierarchyTreeMenuMoveDown);

	GUI_HierarchyTree->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(GUI_MainFrame::GUI_HierarchyTreeOnContextMenu), NULL, this);

	GUI_SizerHierarchy->Add(GUI_HierarchyTree, 1, wxEXPAND, 5);


	GUI_PanelHierarchy->SetSizer(GUI_SizerHierarchy);
	GUI_PanelHierarchy->Layout();
	GUI_SizerHierarchy->Fit(GUI_PanelHierarchy);
	GUI_PanelAssets = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GUI_PanelAssets->SetScrollRate(5, 5);
	m_mgr.AddPane(GUI_PanelAssets, wxAuiPaneInfo().Right().Caption(wxT("Assets")).CloseButton(false).Dock().Resizable().FloatingSize(wxSize(166, 59)).Row(1).MinSize(wxSize(150, 300)));

	wxBoxSizer* GUI_SizerAssets;
	GUI_SizerAssets = new wxBoxSizer(wxVERTICAL);

	GUI_AssetsDirCtrl = new wxMyGenericDirCtrl(GUI_PanelAssets, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRCTRL_EDIT_LABELS | wxSUNKEN_BORDER, wxEmptyString, 0);

	GUI_AssetsDirCtrl->ShowHidden(false);
	GUI_AssetsDirCtrlMenu = new wxMenu();
	wxMenuItem* GUI_AssetsDirCtrlMenuAdd;
	GUI_AssetsDirCtrlMenuAdd = new wxMenuItem(GUI_AssetsDirCtrlMenu, wxID_ANY, wxString(wxT("Add as component")), wxEmptyString, wxITEM_NORMAL);
	GUI_AssetsDirCtrlMenu->Append(GUI_AssetsDirCtrlMenuAdd);

	GUI_AssetsDirCtrl->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(GUI_MainFrame::GUI_AssetsDirCtrlOnContextMenu), NULL, this);

	GUI_SizerAssets->Add(GUI_AssetsDirCtrl, 1, wxEXPAND, 5);

	GUI_AssetsOpen = new wxButton(GUI_PanelAssets, wxID_ANY, wxT("Open"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_SizerAssets->Add(GUI_AssetsOpen, 0, wxALL | wxEXPAND, 5);

	GUI_AssetsRefresh = new wxButton(GUI_PanelAssets, wxID_ANY, wxT("Refresh"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_SizerAssets->Add(GUI_AssetsRefresh, 0, wxALL | wxEXPAND, 5);


	GUI_PanelAssets->SetSizer(GUI_SizerAssets);
	GUI_PanelAssets->Layout();
	GUI_SizerAssets->Fit(GUI_PanelAssets);
	GUI_PanelProperties = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GUI_PanelProperties->SetScrollRate(5, 5);
	m_mgr.AddPane(GUI_PanelProperties, wxAuiPaneInfo().Right().Caption(wxT("Properties")).CloseButton(false).Dock().Resizable().FloatingSize(wxSize(116, 54)).MinSize(wxSize(280, 300)).Layer(7));

	wxBoxSizer* GUI_SizerProperties;
	GUI_SizerProperties = new wxBoxSizer(wxVERTICAL);

	GUI_PropertyRefresh = new wxButton(GUI_PanelProperties, wxID_ANY, wxT("Refresh"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_SizerProperties->Add(GUI_PropertyRefresh, 0, wxALL | wxEXPAND, 5);

	GUI_PropertyGrid = new wxPropertyGrid(GUI_PanelProperties, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE | wxPG_SPLITTER_AUTO_CENTER | wxTAB_TRAVERSAL);
	GUI_SizerProperties->Add(GUI_PropertyGrid, 1, wxEXPAND, 5);

	GUI_ProjectProperty = new wxPropertyGrid(GUI_PanelProperties, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE | wxPG_SPLITTER_AUTO_CENTER | wxTAB_TRAVERSAL);
	GUI_ProjectProperty->SetMinSize(wxSize(-1, 124));

	GUI_ProjectPropertyCategory = GUI_ProjectProperty->Append(new wxPropertyCategory(wxT("Project"), wxT("Project")));
	GUI_ProjectPropertyPath = GUI_ProjectProperty->Append(new wxDirProperty(wxT("Path"), wxT("Path")));
	GUI_ProjectPropertyName = GUI_ProjectProperty->Append(new wxStringProperty(wxT("Name"), wxT("Name")));
	GUI_ProjectPropertyResolutionCategory = GUI_ProjectProperty->Append(new wxPropertyCategory(wxT("Resolution"), wxT("Resolution")));
	GUI_ProjectPropertyWidth = GUI_ProjectProperty->Append(new wxUIntProperty(wxT("Width"), wxT("Width")));
	GUI_ProjectPropertyHeight = GUI_ProjectProperty->Append(new wxUIntProperty(wxT("Height"), wxT("Height")));
	GUI_SizerProperties->Add(GUI_ProjectProperty, 0, wxEXPAND, 5);


	GUI_PanelProperties->SetSizer(GUI_SizerProperties);
	GUI_PanelProperties->Layout();
	GUI_SizerProperties->Fit(GUI_PanelProperties);
	GUI_PanelEditor = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_mgr.AddPane(GUI_PanelEditor, wxAuiPaneInfo().Center().Caption(wxT("Editor")).CloseButton(false).Dock().Resizable().FloatingSize(wxSize(-1, -1)));

	wxGridSizer* GUI_SizerEditor;
	GUI_SizerEditor = new wxGridSizer(0, 1, 0, 0);

	GUI_EditorSFML = new SFMLEditorCanvas(GUI_PanelEditor, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);
	GUI_EditorSFML->SetExtraStyle(wxWS_EX_PROCESS_IDLE);

	GUI_SizerEditor->Add(GUI_EditorSFML, 0, 0, 5);


	GUI_PanelEditor->SetSizer(GUI_SizerEditor);
	GUI_PanelEditor->Layout();
	GUI_SizerEditor->Fit(GUI_PanelEditor);
	GUI_PanelPreview = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_mgr.AddPane(GUI_PanelPreview, wxAuiPaneInfo().Center().Caption(wxT("Game")).CloseButton(false).MaximizeButton(true).Dock().Resizable().FloatingSize(wxDefaultSize));

	wxGridSizer* GUI_SizerPreview;
	GUI_SizerPreview = new wxGridSizer(0, 1, 0, 0);

	GUI_PreviewSFML = new SFMLCanvas(GUI_PanelPreview, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);
	GUI_PreviewSFML->SetExtraStyle(wxWS_EX_PROCESS_IDLE);

	GUI_SizerPreview->Add(GUI_PreviewSFML, 0, 0, 5);


	GUI_PanelPreview->SetSizer(GUI_SizerPreview);
	GUI_PanelPreview->Layout();
	GUI_SizerPreview->Fit(GUI_PanelPreview);
	GUI_MenuBar = new wxMenuBar(0);
	GUI_MenuFile = new wxMenu();
	wxMenuItem* GUI_MenuFileNew;
	GUI_MenuFileNew = new wxMenuItem(GUI_MenuFile, wxID_ANY, wxString(wxT("New")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuFile->Append(GUI_MenuFileNew);

	wxMenuItem* GUI_MenuFileOpen;
	GUI_MenuFileOpen = new wxMenuItem(GUI_MenuFile, wxID_ANY, wxString(wxT("Open")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuFile->Append(GUI_MenuFileOpen);

	wxMenuItem* GUI_MenuFileSave;
	GUI_MenuFileSave = new wxMenuItem(GUI_MenuFile, wxID_ANY, wxString(wxT("Save")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuFile->Append(GUI_MenuFileSave);

	GUI_MenuFile->AppendSeparator();

	wxMenuItem* GUI_MenuFileOpenProject;
	GUI_MenuFileOpenProject = new wxMenuItem(GUI_MenuFile, wxID_ANY, wxString(wxT("Open Project")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuFile->Append(GUI_MenuFileOpenProject);

	wxMenuItem* GUI_MenuFileSaveProject;
	GUI_MenuFileSaveProject = new wxMenuItem(GUI_MenuFile, wxID_ANY, wxString(wxT("Save Project")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuFile->Append(GUI_MenuFileSaveProject);

	GUI_MenuBar->Append(GUI_MenuFile, wxT("File"));

	GUI_MenuGameObject = new wxMenu();
	wxMenuItem* GUI_MenuGameObjectCreateEmpty;
	GUI_MenuGameObjectCreateEmpty = new wxMenuItem(GUI_MenuGameObject, wxID_ANY, wxString(wxT("Create Empty")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuGameObject->Append(GUI_MenuGameObjectCreateEmpty);

	GUI_MenuBar->Append(GUI_MenuGameObject, wxT("GameObject"));

	GUI_MenuComponent = new wxMenu();
	GUI_MenuComponentSubRender = new wxMenu();
	wxMenuItem* GUI_MenuComponentSubRenderItem = new wxMenuItem(GUI_MenuComponent, wxID_ANY, wxT("Render"), wxEmptyString, wxITEM_NORMAL, GUI_MenuComponentSubRender);
	wxMenuItem* GUI_MenuComponentSubRenderSprite;
	GUI_MenuComponentSubRenderSprite = new wxMenuItem(GUI_MenuComponentSubRender, wxID_ANY, wxString(wxT("Sprite")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuComponentSubRender->Append(GUI_MenuComponentSubRenderSprite);

	wxMenuItem* GUI_MenuComponentSubRenderCamera;
	GUI_MenuComponentSubRenderCamera = new wxMenuItem(GUI_MenuComponentSubRender, wxID_ANY, wxString(wxT("Camera")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuComponentSubRender->Append(GUI_MenuComponentSubRenderCamera);

	GUI_MenuComponent->Append(GUI_MenuComponentSubRenderItem);

	wxMenuItem* GUI_MenuComponentScript;
	GUI_MenuComponentScript = new wxMenuItem(GUI_MenuComponent, wxID_ANY, wxString(wxT("Script")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuComponent->Append(GUI_MenuComponentScript);

	wxMenuItem* GUI_MenuComponentParticleSystem;
	GUI_MenuComponentParticleSystem = new wxMenuItem(GUI_MenuComponent, wxID_ANY, wxString(wxT("Particle System")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuComponent->Append(GUI_MenuComponentParticleSystem);

	GUI_MenuBar->Append(GUI_MenuComponent, wxT("Component"));

	GUI_MenuGame = new wxMenu();
	wxMenuItem* GUI_MenuGamePlay;
	GUI_MenuGamePlay = new wxMenuItem(GUI_MenuGame, wxID_ANY, wxString(wxT("Play")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuGame->Append(GUI_MenuGamePlay);

	wxMenuItem* GUI_MenuGameStop;
	GUI_MenuGameStop = new wxMenuItem(GUI_MenuGame, wxID_ANY, wxString(wxT("Stop")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuGame->Append(GUI_MenuGameStop);

	wxMenuItem* GUI_MenuGamePause;
	GUI_MenuGamePause = new wxMenuItem(GUI_MenuGame, wxID_ANY, wxString(wxT("Pause")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuGame->Append(GUI_MenuGamePause);

	GUI_MenuBar->Append(GUI_MenuGame, wxT("Game"));

	this->SetMenuBar(GUI_MenuBar);

	GUI_StatusBar = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);

	m_mgr.Update();
	this->Centre(wxBOTH);

	// Connect Events
	GUI_HierarchyTree->Connect(wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeEndLabelEdit), NULL, this);
	GUI_HierarchyTree->Connect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeSelChanged), NULL, this);
	this->Connect(GUI_HierarchyTreeMenuRemove->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuRemove_OnMenuSelection));
	this->Connect(GUI_HierarchyTreeMenuMoveUp->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuMoveUp_OnMenuSelection));
	this->Connect(GUI_HierarchyTreeMenuMoveDown->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuMoveDown_OnMenuSelection));
	GUI_AssetsDirCtrl->Connect(wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler(GUI_MainFrame::GUI_AssetsDirCtrl_OnBeginDrag), NULL, this);
	this->Connect(GUI_AssetsDirCtrlMenuAdd->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_AssetsDirCtrlMenuAdd_OnMenuSelection));
	GUI_AssetsOpen->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_MainFrame::GUI_AssetsOpen_OnButtonClick), NULL, this);
	GUI_AssetsRefresh->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_MainFrame::GUI_AssetsRefresh_OnButtonClick), NULL, this);
	GUI_PropertyRefresh->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_MainFrame::GUI_PropertyRefresh_OnButtonClick), NULL, this);
	GUI_PropertyGrid->Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(GUI_MainFrame::GUI_PropertyGrid_OnPropertyGridChanged), NULL, this);
	GUI_PanelEditor->Connect(wxEVT_SIZE, wxSizeEventHandler(GUI_MainFrame::GUI_PanelEditor_OnSize), NULL, this);
	GUI_PanelPreview->Connect(wxEVT_SIZE, wxSizeEventHandler(GUI_MainFrame::GUI_PanelPreview_OnSize), NULL, this);
	this->Connect(GUI_MenuFileNew->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuFileNew_OnMenuSelection));
	this->Connect(GUI_MenuFileOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuFileOpen_OnMenuSelection));
	this->Connect(GUI_MenuFileSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuFileSave_OnMenuSelection));
	this->Connect(GUI_MenuFileOpenProject->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuFileOpenProject_OnMenuSelection));
	this->Connect(GUI_MenuFileSaveProject->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuFileSaveProject_OnMenuSelection));
	this->Connect(GUI_MenuGameObjectCreateEmpty->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGameObjectCreateEmpty_OnMenuSelection));
	this->Connect(GUI_MenuComponentSubRenderSprite->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuComponentSubRenderSprite_OnMenuSelection));
	this->Connect(GUI_MenuComponentSubRenderCamera->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuComponentSubRenderCamera_OnMenuSelection));
	this->Connect(GUI_MenuComponentScript->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuComponentScript_OnMenuSelection));
	this->Connect(GUI_MenuComponentParticleSystem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuComponentParticleSystem_OnMenuSelection));
	this->Connect(GUI_MenuGamePlay->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGamePlay_OnMenuSelection));
	this->Connect(GUI_MenuGameStop->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGameStop_OnMenuSelection));
	this->Connect(GUI_MenuGamePause->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGamePause_OnMenuSelection));
}

GUI_MainFrame::~GUI_MainFrame()
{
	// Disconnect Events
	GUI_HierarchyTree->Disconnect(wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeEndLabelEdit), NULL, this);
	GUI_HierarchyTree->Disconnect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeSelChanged), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuRemove_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuMoveUp_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuMoveDown_OnMenuSelection));
	GUI_AssetsDirCtrl->Disconnect(wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler(GUI_MainFrame::GUI_AssetsDirCtrl_OnBeginDrag), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_AssetsDirCtrlMenuAdd_OnMenuSelection));
	GUI_AssetsOpen->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_MainFrame::GUI_AssetsOpen_OnButtonClick), NULL, this);
	GUI_AssetsRefresh->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_MainFrame::GUI_AssetsRefresh_OnButtonClick), NULL, this);
	GUI_PropertyRefresh->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_MainFrame::GUI_PropertyRefresh_OnButtonClick), NULL, this);
	GUI_PropertyGrid->Disconnect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(GUI_MainFrame::GUI_PropertyGrid_OnPropertyGridChanged), NULL, this);
	GUI_PanelEditor->Disconnect(wxEVT_SIZE, wxSizeEventHandler(GUI_MainFrame::GUI_PanelEditor_OnSize), NULL, this);
	GUI_PanelPreview->Disconnect(wxEVT_SIZE, wxSizeEventHandler(GUI_MainFrame::GUI_PanelPreview_OnSize), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuFileNew_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuFileOpen_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuFileSave_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuFileOpenProject_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuFileSaveProject_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGameObjectCreateEmpty_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuComponentSubRenderSprite_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuComponentSubRenderCamera_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuComponentScript_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuComponentParticleSystem_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGamePlay_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGameStop_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGamePause_OnMenuSelection));

	m_mgr.UnInit();

	delete GUI_HierarchyTreeMenu;
}
