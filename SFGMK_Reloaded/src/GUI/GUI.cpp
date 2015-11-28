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

	GUI_HierarchyTree = new wxTreeCtrl(GUI_PanelHierarchy, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_EDIT_LABELS | wxTR_HAS_BUTTONS | wxTR_HIDE_ROOT | wxTR_LINES_AT_ROOT);
	GUI_SizerHierarchy->Add(GUI_HierarchyTree, 1, wxEXPAND, 5);


	GUI_PanelHierarchy->SetSizer(GUI_SizerHierarchy);
	GUI_PanelHierarchy->Layout();
	GUI_SizerHierarchy->Fit(GUI_PanelHierarchy);
	GUI_PanelAssets = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GUI_PanelAssets->SetScrollRate(5, 5);
	m_mgr.AddPane(GUI_PanelAssets, wxAuiPaneInfo().Right().Caption(wxT("Assets")).CloseButton(false).Dock().Resizable().FloatingSize(wxSize(166, 59)).Row(1).MinSize(wxSize(150, 300)));

	wxBoxSizer* GUI_SizerAssets;
	GUI_SizerAssets = new wxBoxSizer(wxVERTICAL);


	GUI_PanelAssets->SetSizer(GUI_SizerAssets);
	GUI_PanelAssets->Layout();
	GUI_SizerAssets->Fit(GUI_PanelAssets);
	GUI_PanelProperties = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GUI_PanelProperties->SetScrollRate(5, 5);
	m_mgr.AddPane(GUI_PanelProperties, wxAuiPaneInfo().Right().Caption(wxT("Properties")).CloseButton(false).Dock().Resizable().FloatingSize(wxSize(116, 54)).MinSize(wxSize(280, 300)).Layer(7));

	wxBoxSizer* GUI_SizerProperties;
	GUI_SizerProperties = new wxBoxSizer(wxVERTICAL);

	GUI_PropertyGrid = new wxPropertyGrid(GUI_PanelProperties, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE | wxPG_SPLITTER_AUTO_CENTER | wxTAB_TRAVERSAL);
	GUI_PropGameObject = GUI_PropertyGrid->Append(new wxPropertyCategory(wxT("GameObject"), wxT("GameObject")));
	GUI_PropGameObjectName = GUI_PropertyGrid->Append(new wxStringProperty(wxT("Name"), wxT("Name")));
	GUI_PropTransformCategory = GUI_PropertyGrid->Append(new wxPropertyCategory(wxT("Transform"), wxT("Transform")));
	GUI_PropTransformPosX = GUI_PropertyGrid->Append(new wxFloatProperty(wxT("Pos X"), wxT("Pos X")));
	GUI_PropTransformPosY = GUI_PropertyGrid->Append(new wxFloatProperty(wxT("Pos Y"), wxT("Pos Y")));
	GUI_PropTransformScaleX = GUI_PropertyGrid->Append(new wxFloatProperty(wxT("Scale X"), wxT("Scale X")));
	GUI_PropTransformScaleY = GUI_PropertyGrid->Append(new wxFloatProperty(wxT("Scale Y"), wxT("Scale Y")));
	GUI_PropTransformRotation = GUI_PropertyGrid->Append(new wxFloatProperty(wxT("Rotation"), wxT("Rotation")));
	GUI_SizerProperties->Add(GUI_PropertyGrid, 1, wxEXPAND, 5);


	GUI_PanelProperties->SetSizer(GUI_SizerProperties);
	GUI_PanelProperties->Layout();
	GUI_SizerProperties->Fit(GUI_PanelProperties);
	GUI_PanelEditor = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_mgr.AddPane(GUI_PanelEditor, wxAuiPaneInfo().Center().Caption(wxT("Editor")).CloseButton(false).MaximizeButton(true).Dock().Resizable().FloatingSize(wxSize(-1, -1)));

	wxGridSizer* GUI_SizerEditor;
	GUI_SizerEditor = new wxGridSizer(0, 1, 0, 0);

	GUI_EditorSFML = new wxSFMLEditorCanvas(GUI_PanelEditor, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);
	GUI_SizerEditor->Add(GUI_EditorSFML, 0, 0, 5);


	GUI_PanelEditor->SetSizer(GUI_SizerEditor);
	GUI_PanelEditor->Layout();
	GUI_SizerEditor->Fit(GUI_PanelEditor);
	GUI_PanelPreview = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_mgr.AddPane(GUI_PanelPreview, wxAuiPaneInfo().Center().Caption(wxT("Game")).CloseButton(false).MaximizeButton(true).Dock().Resizable().FloatingSize(wxDefaultSize));

	wxGridSizer* GUI_SizerPreview;
	GUI_SizerPreview = new wxGridSizer(0, 1, 0, 0);

	GUI_PreviewSFML = new wxSFMLCanvas(GUI_PanelPreview, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);
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

	GUI_MenuComponent->Append(GUI_MenuComponentSubRenderItem);

	GUI_MenuBar->Append(GUI_MenuComponent, wxT("Component"));

	GUI_MenuGame = new wxMenu();
	wxMenuItem* GUI_MenuGameStart;
	GUI_MenuGameStart = new wxMenuItem(GUI_MenuGame, wxID_ANY, wxString(wxT("Start")) + wxT('\t') + wxT("F5"), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuGame->Append(GUI_MenuGameStart);

	wxMenuItem* GUI_MenuGameStop;
	GUI_MenuGameStop = new wxMenuItem(GUI_MenuGame, wxID_ANY, wxString(wxT("Stop")) + wxT('\t') + wxT("Shift + F5"), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuGame->Append(GUI_MenuGameStop);

	wxMenuItem* GUI_MenuGamePause;
	GUI_MenuGamePause = new wxMenuItem(GUI_MenuGame, wxID_ANY, wxString(wxT("Pause")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuGame->Append(GUI_MenuGamePause);

	GUI_MenuBar->Append(GUI_MenuGame, wxT("Game"));

	this->SetMenuBar(GUI_MenuBar);


	m_mgr.Update();
	this->Centre(wxBOTH);

	// Connect Events
	GUI_HierarchyTree->Connect(wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeEndLabelEdit), NULL, this);
	GUI_HierarchyTree->Connect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeSelChanged), NULL, this);
	GUI_PropertyGrid->Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(GUI_MainFrame::GUI_PropertyGrid_OnPropertyGridChanged), NULL, this);
	GUI_PanelEditor->Connect(wxEVT_SIZE, wxSizeEventHandler(GUI_MainFrame::GUI_PanelEditor_OnSize), NULL, this);
	GUI_PanelPreview->Connect(wxEVT_SIZE, wxSizeEventHandler(GUI_MainFrame::GUI_PanelPreview_OnSize), NULL, this);
	this->Connect(GUI_MenuGameObjectCreateEmpty->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGameObjectCreateEmpty_OnMenuSelection));
	this->Connect(GUI_MenuComponentSubRenderSprite->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuComponentSubRenderSprite_OnMenuSelection));
}

GUI_MainFrame::~GUI_MainFrame()
{
	// Disconnect Events
	GUI_HierarchyTree->Disconnect(wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeEndLabelEdit), NULL, this);
	GUI_HierarchyTree->Disconnect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeSelChanged), NULL, this);
	GUI_PropertyGrid->Disconnect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler(GUI_MainFrame::GUI_PropertyGrid_OnPropertyGridChanged), NULL, this);
	GUI_PanelEditor->Disconnect(wxEVT_SIZE, wxSizeEventHandler(GUI_MainFrame::GUI_PanelEditor_OnSize), NULL, this);
	GUI_PanelPreview->Disconnect(wxEVT_SIZE, wxSizeEventHandler(GUI_MainFrame::GUI_PanelPreview_OnSize), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGameObjectCreateEmpty_OnMenuSelection));
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuComponentSubRenderSprite_OnMenuSelection));

	m_mgr.UnInit();

}
