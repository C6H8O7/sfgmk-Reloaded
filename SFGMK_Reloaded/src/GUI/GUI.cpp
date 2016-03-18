///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

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

	wxMenuItem* GUI_HierarchyTreeMenuDuplicate;
	GUI_HierarchyTreeMenuDuplicate = new wxMenuItem(GUI_HierarchyTreeMenu, wxID_ANY, wxString(wxT("Duplicate")), wxEmptyString, wxITEM_NORMAL);
	GUI_HierarchyTreeMenu->Append(GUI_HierarchyTreeMenuDuplicate);

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

	GUI_MenuView = new wxMenu();
	wxMenuItem* GUI_MenuViewProject;
	GUI_MenuViewProject = new wxMenuItem(GUI_MenuView, wxID_ANY, wxString(wxT("Project")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuView->Append(GUI_MenuViewProject);

	wxMenuItem* GUI_MenuViewScriptEditor;
	GUI_MenuViewScriptEditor = new wxMenuItem(GUI_MenuView, wxID_ANY, wxString(wxT("Script Editor")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuView->Append(GUI_MenuViewScriptEditor);

	wxMenuItem* GUI_MenuViewBehaviorTree;
	GUI_MenuViewBehaviorTree = new wxMenuItem(GUI_MenuView, wxID_ANY, wxString(wxT("Behavior Tree")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuView->Append(GUI_MenuViewBehaviorTree);

	GUI_MenuBar->Append(GUI_MenuView, wxT("View"));

	GUI_MenuGameObject = new wxMenu();
	wxMenuItem* GUI_MenuGameObjectCreateEmpty;
	GUI_MenuGameObjectCreateEmpty = new wxMenuItem(GUI_MenuGameObject, wxID_ANY, wxString(wxT("Create Empty")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuGameObject->Append(GUI_MenuGameObjectCreateEmpty);

	GUI_MenuBar->Append(GUI_MenuGameObject, wxT("GameObject"));

	GUI_MenuComponent = new wxMenu();
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
	GUI_PanelProject = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GUI_PanelProject->SetScrollRate(5, 5);
	m_mgr.AddPane(GUI_PanelProject, wxAuiPaneInfo().Right().Caption(wxT("Project")).Hide().Float().FloatingPosition(wxPoint(25, 25)).Resizable().FloatingSize(wxSize(266, 488)).MinSize(wxSize(250, 450)).Layer(7));

	wxBoxSizer* GUI_SizerProject;
	GUI_SizerProject = new wxBoxSizer(wxVERTICAL);

	GUI_ProjectProperty = new wxPropertyGrid(GUI_PanelProject, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE | wxPG_SPLITTER_AUTO_CENTER | wxTAB_TRAVERSAL);
	GUI_ProjectProperty->SetMinSize(wxSize(-1, 124));

	GUI_ProjectPropertyCategory = GUI_ProjectProperty->Append(new wxPropertyCategory(wxT("Project"), wxT("Project")));
	GUI_ProjectPropertyPath = GUI_ProjectProperty->Append(new wxDirProperty(wxT("Path"), wxT("Path")));
	GUI_ProjectPropertyName = GUI_ProjectProperty->Append(new wxStringProperty(wxT("Name"), wxT("Name")));
	wxPGProperty* GUI_ProjectPropertyResolutionCategory;
	GUI_ProjectPropertyResolutionCategory = GUI_ProjectProperty->Append(new wxPropertyCategory(wxT("Resolution"), wxT("Resolution")));
	GUI_ProjectPropertyWidth = GUI_ProjectProperty->Append(new wxUIntProperty(wxT("Width"), wxT("Width")));
	GUI_ProjectPropertyHeight = GUI_ProjectProperty->Append(new wxUIntProperty(wxT("Height"), wxT("Height")));
	GUI_SizerProject->Add(GUI_ProjectProperty, 1, wxEXPAND, 5);


	GUI_PanelProject->SetSizer(GUI_SizerProject);
	GUI_PanelProject->Layout();
	GUI_SizerProject->Fit(GUI_PanelProject);
	GUI_PanelScript = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GUI_PanelScript->SetScrollRate(5, 5);
	m_mgr.AddPane(GUI_PanelScript, wxAuiPaneInfo().Right().Caption(wxT("Script Editor")).Hide().Float().FloatingPosition(wxPoint(526, 305)).Resizable().FloatingSize(wxSize(916, 538)).BottomDockable(false).TopDockable(false).LeftDockable(false).RightDockable(false).Row(0).MinSize(wxSize(900, 500)).Layer(7));

	wxBoxSizer* GUI_SizerScript;
	GUI_SizerScript = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* GUI_SizerScriptTools;
	GUI_SizerScriptTools = new wxBoxSizer(wxHORIZONTAL);

	GUI_ScriptSelNum = new wxStaticText(GUI_PanelScript, wxID_ANY, wxT("0 / 0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
	GUI_ScriptSelNum->Wrap(-1);
	GUI_ScriptSelNum->SetMinSize(wxSize(35, -1));

	GUI_SizerScriptTools->Add(GUI_ScriptSelNum, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	GUI_ScriptSelSpin = new wxSpinButton(GUI_PanelScript, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_HORIZONTAL);
	GUI_SizerScriptTools->Add(GUI_ScriptSelSpin, 0, wxALL | wxEXPAND, 5);

	GUI_ScriptSelName = new wxStaticText(GUI_PanelScript, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	GUI_ScriptSelName->Wrap(-1);
	GUI_SizerScriptTools->Add(GUI_ScriptSelName, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	GUI_ScriptSave = new wxButton(GUI_PanelScript, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	GUI_SizerScriptTools->Add(GUI_ScriptSave, 0, wxALL, 5);

	GUI_ScriptClose = new wxButton(GUI_PanelScript, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	GUI_SizerScriptTools->Add(GUI_ScriptClose, 0, wxALL, 5);


	GUI_SizerScript->Add(GUI_SizerScriptTools, 0, wxEXPAND, 5);

	GUI_ScriptEditor = new wxStyledTextCtrl(GUI_PanelScript, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxEmptyString);
	GUI_ScriptEditor->SetUseTabs(true);
	GUI_ScriptEditor->SetTabWidth(10);
	GUI_ScriptEditor->SetIndent(10);
	GUI_ScriptEditor->SetTabIndents(true);
	GUI_ScriptEditor->SetBackSpaceUnIndents(true);
	GUI_ScriptEditor->SetViewEOL(false);
	GUI_ScriptEditor->SetViewWhiteSpace(false);
	GUI_ScriptEditor->SetMarginWidth(2, 0);
	GUI_ScriptEditor->SetIndentationGuides(true);
	GUI_ScriptEditor->SetMarginType(1, wxSTC_MARGIN_SYMBOL);
	GUI_ScriptEditor->SetMarginMask(1, wxSTC_MASK_FOLDERS);
	GUI_ScriptEditor->SetMarginWidth(1, 16);
	GUI_ScriptEditor->SetMarginSensitive(1, true);
	GUI_ScriptEditor->SetProperty(wxT("fold"), wxT("1"));
	GUI_ScriptEditor->SetFoldFlags(wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);
	GUI_ScriptEditor->SetMarginType(0, wxSTC_MARGIN_NUMBER);
	GUI_ScriptEditor->SetMarginWidth(0, GUI_ScriptEditor->TextWidth(wxSTC_STYLE_LINENUMBER, wxT("_99999")));
	GUI_ScriptEditor->MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS);
	GUI_ScriptEditor->MarkerSetBackground(wxSTC_MARKNUM_FOLDER, wxColour(wxT("BLACK")));
	GUI_ScriptEditor->MarkerSetForeground(wxSTC_MARKNUM_FOLDER, wxColour(wxT("WHITE")));
	GUI_ScriptEditor->MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS);
	GUI_ScriptEditor->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPEN, wxColour(wxT("BLACK")));
	GUI_ScriptEditor->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPEN, wxColour(wxT("WHITE")));
	GUI_ScriptEditor->MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY);
	GUI_ScriptEditor->MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS);
	GUI_ScriptEditor->MarkerSetBackground(wxSTC_MARKNUM_FOLDEREND, wxColour(wxT("BLACK")));
	GUI_ScriptEditor->MarkerSetForeground(wxSTC_MARKNUM_FOLDEREND, wxColour(wxT("WHITE")));
	GUI_ScriptEditor->MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS);
	GUI_ScriptEditor->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPENMID, wxColour(wxT("BLACK")));
	GUI_ScriptEditor->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPENMID, wxColour(wxT("WHITE")));
	GUI_ScriptEditor->MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY);
	GUI_ScriptEditor->MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY);
	GUI_ScriptEditor->SetSelBackground(true, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
	GUI_ScriptEditor->SetSelForeground(true, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
	GUI_SizerScript->Add(GUI_ScriptEditor, 1, wxEXPAND | wxALL, 5);


	GUI_PanelScript->SetSizer(GUI_SizerScript);
	GUI_PanelScript->Layout();
	GUI_SizerScript->Fit(GUI_PanelScript);
	GUI_PanelBehaviorTree = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GUI_PanelBehaviorTree->SetScrollRate(5, 5);
	m_mgr.AddPane(GUI_PanelBehaviorTree, wxAuiPaneInfo().Right().Caption(wxT("Behavior Tree")).Hide().Float().FloatingPosition(wxPoint(526, 305)).Resizable().FloatingSize(wxSize(916, 538)).BottomDockable(false).TopDockable(false).LeftDockable(false).RightDockable(false).Row(0).MinSize(wxSize(900, 500)).Layer(7));

	wxBoxSizer* GUI_SizerBehaviorTree;
	GUI_SizerBehaviorTree = new wxBoxSizer(wxVERTICAL);

	GUI_BehaviorTree = new wxWorkspaceView(GUI_PanelBehaviorTree, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	GUI_SizerBehaviorTree->Add(GUI_BehaviorTree, 1, wxEXPAND | wxALL, 5);


	GUI_PanelBehaviorTree->SetSizer(GUI_SizerBehaviorTree);
	GUI_PanelBehaviorTree->Layout();
	GUI_SizerBehaviorTree->Fit(GUI_PanelBehaviorTree);

	m_mgr.Update();
	this->Centre(wxBOTH);

	// Connect Events
	GUI_HierarchyTree->Connect(wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeBeginDrag), NULL, this);
	GUI_HierarchyTree->Connect(wxEVT_COMMAND_TREE_END_DRAG, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeEndDrag), NULL, this);
	GUI_HierarchyTree->Connect(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeItemActivated), NULL, this);
	GUI_HierarchyTree->Connect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeSelChanged), NULL, this);
	this->Connect(GUI_HierarchyTreeMenuRemove->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuRemove_OnMenuSelection));
	this->Connect(GUI_HierarchyTreeMenuMoveUp->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuMoveUp_OnMenuSelection));
	this->Connect(GUI_HierarchyTreeMenuMoveDown->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuMoveDown_OnMenuSelection));
	this->Connect(GUI_HierarchyTreeMenuDuplicate->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuDuplicate_OnMenuSelection));
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
	this->Connect(GUI_MenuViewProject->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuViewProject_OnMenuSelection));
	this->Connect(GUI_MenuViewScriptEditor->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuViewScriptEditor_OnMenuSelection));
	this->Connect(GUI_MenuViewBehaviorTree->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuViewBehaviorTree_OnMenuSelection));
	this->Connect(GUI_MenuGameObjectCreateEmpty->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGameObjectCreateEmpty_OnMenuSelection));
	this->Connect(GUI_MenuGamePlay->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGamePlay_OnMenuSelection));
	this->Connect(GUI_MenuGameStop->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGameStop_OnMenuSelection));
	this->Connect(GUI_MenuGamePause->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGamePause_OnMenuSelection));
	GUI_ProjectProperty->Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(GUI_MainFrame::GUI_ProjectProperty_OnPropertyGridChanged), NULL, this);
	GUI_ScriptSelSpin->Connect(wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler(GUI_MainFrame::GUI_ScriptSelSpin_OnSpin), NULL, this);
	GUI_ScriptSave->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_MainFrame::GUI_ScriptSave_OnButtonClick), NULL, this);
	GUI_ScriptClose->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_MainFrame::GUI_ScriptClose_OnButtonClick), NULL, this);
}

GUI_MainFrame::~GUI_MainFrame()
{
	// Disconnect Events
	GUI_HierarchyTree->Disconnect(wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeBeginDrag), NULL, this);
	GUI_HierarchyTree->Disconnect(wxEVT_COMMAND_TREE_END_DRAG, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeEndDrag), NULL, this);
	GUI_HierarchyTree->Disconnect(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeItemActivated), NULL, this);
	GUI_HierarchyTree->Disconnect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeSelChanged), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuRemove_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuMoveUp_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuMoveDown_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_HierarchyTreeMenuDuplicate_OnMenuSelection));
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
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuViewProject_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuViewScriptEditor_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuViewBehaviorTree_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGameObjectCreateEmpty_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGamePlay_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGameStop_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGamePause_OnMenuSelection));
	GUI_ProjectProperty->Disconnect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(GUI_MainFrame::GUI_ProjectProperty_OnPropertyGridChanged), NULL, this);
	GUI_ScriptSelSpin->Disconnect(wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler(GUI_MainFrame::GUI_ScriptSelSpin_OnSpin), NULL, this);
	GUI_ScriptSave->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_MainFrame::GUI_ScriptSave_OnButtonClick), NULL, this);
	GUI_ScriptClose->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_MainFrame::GUI_ScriptClose_OnButtonClick), NULL, this);

	m_mgr.UnInit();

	delete GUI_HierarchyTreeMenu;
}
