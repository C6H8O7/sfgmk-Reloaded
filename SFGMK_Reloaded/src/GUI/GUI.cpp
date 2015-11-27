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

	wxBoxSizer* GUI_SizerTransform;
	GUI_SizerTransform = new wxBoxSizer(wxVERTICAL);

	GUI_TextTransform = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("Transform"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextTransform->Wrap(-1);
	GUI_SizerTransform->Add(GUI_TextTransform, 0, wxALL, 5);

	wxBoxSizer* GUI_SizerPosition;
	GUI_SizerPosition = new wxBoxSizer(wxHORIZONTAL);

	GUI_TextPosition = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("Position"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextPosition->Wrap(-1);
	GUI_SizerPosition->Add(GUI_TextPosition, 1, wxALL, 5);

	GUI_TextX = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("X"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextX->Wrap(-1);
	GUI_SizerPosition->Add(GUI_TextX, 0, wxALL, 5);

	GUI_PosX = new wxTextCtrl(GUI_PanelProperties, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	GUI_PosX->SetMaxSize(wxSize(80, -1));

	GUI_PosX->SetValidator(wxTextValidator(wxFILTER_NUMERIC, &validator_posx));

	GUI_SizerPosition->Add(GUI_PosX, 0, wxALL, 5);

	GUI_TextY = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("Y"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextY->Wrap(-1);
	GUI_SizerPosition->Add(GUI_TextY, 0, wxALL, 5);

	GUI_PosY = new wxTextCtrl(GUI_PanelProperties, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	GUI_PosY->SetMaxSize(wxSize(80, -1));

	GUI_PosY->SetValidator(wxTextValidator(wxFILTER_NUMERIC, &validator_posy));

	GUI_SizerPosition->Add(GUI_PosY, 0, wxALL, 5);


	GUI_SizerTransform->Add(GUI_SizerPosition, 0, 0, 5);

	wxBoxSizer* GUI_SizerScale;
	GUI_SizerScale = new wxBoxSizer(wxHORIZONTAL);

	GUI_TextScale = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("Scale"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextScale->Wrap(-1);
	GUI_SizerScale->Add(GUI_TextScale, 1, wxALL, 5);

	GUI_TextX1 = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("X"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextX1->Wrap(-1);
	GUI_SizerScale->Add(GUI_TextX1, 0, wxALL, 5);

	GUI_ScaleX = new wxTextCtrl(GUI_PanelProperties, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	GUI_ScaleX->SetMaxSize(wxSize(80, -1));

	GUI_ScaleX->SetValidator(wxTextValidator(wxFILTER_NUMERIC, &validator_scalex));

	GUI_SizerScale->Add(GUI_ScaleX, 0, wxALL, 5);

	GUI_TextY1 = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("Y"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextY1->Wrap(-1);
	GUI_SizerScale->Add(GUI_TextY1, 0, wxALL, 5);

	GUI_ScaleY = new wxTextCtrl(GUI_PanelProperties, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	GUI_ScaleY->SetMaxSize(wxSize(80, -1));

	GUI_ScaleY->SetValidator(wxTextValidator(wxFILTER_NUMERIC, &validator_scaley));

	GUI_SizerScale->Add(GUI_ScaleY, 0, wxALL, 5);


	GUI_SizerTransform->Add(GUI_SizerScale, 1, wxEXPAND, 5);

	wxBoxSizer* GUI_SizerScale1;
	GUI_SizerScale1 = new wxBoxSizer(wxHORIZONTAL);

	GUI_TextRotation = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("Rotation"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextRotation->Wrap(-1);
	GUI_SizerScale1->Add(GUI_TextRotation, 1, wxALL, 5);

	GUI_Rotation = new wxTextCtrl(GUI_PanelProperties, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	GUI_Rotation->SetMaxSize(wxSize(80, -1));

	GUI_Rotation->SetValidator(wxTextValidator(wxFILTER_NUMERIC, &validator_rotation));

	GUI_SizerScale1->Add(GUI_Rotation, 0, wxALL, 5);


	GUI_SizerTransform->Add(GUI_SizerScale1, 1, wxEXPAND, 5);


	GUI_SizerProperties->Add(GUI_SizerTransform, 0, 0, 5);


	GUI_PanelProperties->SetSizer(GUI_SizerProperties);
	GUI_PanelProperties->Layout();
	GUI_SizerProperties->Fit(GUI_PanelProperties);
	GUI_PanelEditor = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_mgr.AddPane(GUI_PanelEditor, wxAuiPaneInfo().Center().Caption(wxT("Editor")).CloseButton(false).MaximizeButton(true).Dock().Resizable().FloatingSize(wxSize(-1, -1)));

	wxGridSizer* GUI_SizerEditor;
	GUI_SizerEditor = new wxGridSizer(0, 1, 0, 0);

	GUI_EditorSFML = new wxPanel(GUI_PanelEditor, wxID_ANY, wxDefaultPosition, wxSize(1280, 720), wxTAB_TRAVERSAL);
	GUI_SizerEditor->Add(GUI_EditorSFML, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);


	GUI_PanelEditor->SetSizer(GUI_SizerEditor);
	GUI_PanelEditor->Layout();
	GUI_SizerEditor->Fit(GUI_PanelEditor);
	GUI_PanelPreview = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_mgr.AddPane(GUI_PanelPreview, wxAuiPaneInfo().Center().Caption(wxT("Preview")).CloseButton(false).MaximizeButton(true).Dock().Resizable().FloatingSize(wxDefaultSize));

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

	this->SetMenuBar(GUI_MenuBar);


	m_mgr.Update();
	this->Centre(wxBOTH);

	// Connect Events
	GUI_HierarchyTree->Connect(wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeEndLabelEdit), NULL, this);
	GUI_HierarchyTree->Connect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeSelChanged), NULL, this);
	GUI_PosX->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::GUI_PosX_OnText), NULL, this);
	GUI_PosY->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::GUI_PosY_OnText), NULL, this);
	GUI_ScaleX->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::GUI_ScaleX_OnText), NULL, this);
	GUI_ScaleY->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::GUI_ScaleY_OnText), NULL, this);
	GUI_Rotation->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::GUI_Rotation_OnText), NULL, this);
	GUI_PanelPreview->Connect(wxEVT_SIZE, wxSizeEventHandler(GUI_MainFrame::GUI_PanelPreview_OnSize), NULL, this);
	this->Connect(GUI_MenuGameObjectCreateEmpty->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGameObjectCreateEmpty_OnMenuSelection));
}

GUI_MainFrame::~GUI_MainFrame()
{
	// Disconnect Events
	GUI_HierarchyTree->Disconnect(wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeEndLabelEdit), NULL, this);
	GUI_HierarchyTree->Disconnect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(GUI_MainFrame::GUI_HierarchyTree_OnTreeSelChanged), NULL, this);
	GUI_PosX->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::GUI_PosX_OnText), NULL, this);
	GUI_PosY->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::GUI_PosY_OnText), NULL, this);
	GUI_ScaleX->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::GUI_ScaleX_OnText), NULL, this);
	GUI_ScaleY->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::GUI_ScaleY_OnText), NULL, this);
	GUI_Rotation->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::GUI_Rotation_OnText), NULL, this);
	GUI_PanelPreview->Disconnect(wxEVT_SIZE, wxSizeEventHandler(GUI_MainFrame::GUI_PanelPreview_OnSize), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_MainFrame::GUI_MenuGameObjectCreateEmpty_OnMenuSelection));

	m_mgr.UnInit();

}
