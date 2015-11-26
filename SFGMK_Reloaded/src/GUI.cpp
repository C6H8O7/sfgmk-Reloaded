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

	GUI_PanelProperties = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	GUI_PanelProperties->SetScrollRate(5, 5);
	m_mgr.AddPane(GUI_PanelProperties, wxAuiPaneInfo().Right().Caption(wxT("Properties")).CloseButton(false).Dock().Resizable().FloatingSize(wxSize(116, 54)).MinSize(wxSize(200, -1)).Layer(7));

	wxBoxSizer* GUI_SizerProperties;
	GUI_SizerProperties = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* GUI_Sizer;
	GUI_Sizer = new wxBoxSizer(wxVERTICAL);

	GUI_TextTransform = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("Transform"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextTransform->Wrap(-1);
	GUI_TextTransform->SetFont(wxFont(9, 74, 90, 90, false, wxT("Arial")));

	GUI_Sizer->Add(GUI_TextTransform, 0, wxALL, 5);

	wxBoxSizer* GUI_SizerPosition;
	GUI_SizerPosition = new wxBoxSizer(wxHORIZONTAL);

	GUI_TextPosition = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("Position"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextPosition->Wrap(-1);
	GUI_SizerPosition->Add(GUI_TextPosition, 0, wxALL, 5);

	GUI_TextX = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("X"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextX->Wrap(-1);
	GUI_SizerPosition->Add(GUI_TextX, 0, wxALL, 5);

	GUI_PosX = new wxTextCtrl(GUI_PanelProperties, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	GUI_PosX->SetMaxSize(wxSize(80, -1));

	GUI_SizerPosition->Add(GUI_PosX, 0, wxALL, 5);

	GUI_TextY = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("Y"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextY->Wrap(-1);
	GUI_SizerPosition->Add(GUI_TextY, 0, wxALL, 5);

	GUI_PosY = new wxTextCtrl(GUI_PanelProperties, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	GUI_PosY->SetMaxSize(wxSize(80, -1));

	GUI_SizerPosition->Add(GUI_PosY, 0, wxALL, 5);

	GUI_TextZ = new wxStaticText(GUI_PanelProperties, wxID_ANY, wxT("Z"), wxDefaultPosition, wxDefaultSize, 0);
	GUI_TextZ->Wrap(-1);
	GUI_SizerPosition->Add(GUI_TextZ, 0, wxALL, 5);

	GUI_PosZ = new wxTextCtrl(GUI_PanelProperties, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	GUI_PosZ->SetMaxSize(wxSize(80, -1));

	GUI_SizerPosition->Add(GUI_PosZ, 0, wxALL, 5);


	GUI_Sizer->Add(GUI_SizerPosition, 0, 0, 5);


	GUI_SizerProperties->Add(GUI_Sizer, 0, 0, 5);


	GUI_PanelProperties->SetSizer(GUI_SizerProperties);
	GUI_PanelProperties->Layout();
	GUI_SizerProperties->Fit(GUI_PanelProperties);
	GUI_PanelAssets = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_mgr.AddPane(GUI_PanelAssets, wxAuiPaneInfo().Right().Caption(wxT("Assets")).CloseButton(false).Dock().Resizable().FloatingSize(wxSize(100, 59)).MinSize(wxSize(100, -1)).Layer(6));

	wxBoxSizer* GUI_SizerAssets;
	GUI_SizerAssets = new wxBoxSizer(wxVERTICAL);


	GUI_PanelAssets->SetSizer(GUI_SizerAssets);
	GUI_PanelAssets->Layout();
	GUI_SizerAssets->Fit(GUI_PanelAssets);
	GUI_PanelHierarchy = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_mgr.AddPane(GUI_PanelHierarchy, wxAuiPaneInfo().Right().Caption(wxT("Hierarchy")).CloseButton(false).Dock().Resizable().FloatingSize(wxSize(100, 59)).Row(1).MinSize(wxSize(100, -1)).Layer(0));

	wxBoxSizer* GUI_SizerHierarchy;
	GUI_SizerHierarchy = new wxBoxSizer(wxVERTICAL);


	GUI_PanelHierarchy->SetSizer(GUI_SizerHierarchy);
	GUI_PanelHierarchy->Layout();
	GUI_SizerHierarchy->Fit(GUI_PanelHierarchy);
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

	GUI_PreviewSFML = new wxSFMLCanvas(GUI_PanelPreview, wxID_ANY, wxDefaultPosition, wxSize(1280, 720), wxTAB_TRAVERSAL);
	GUI_SizerPreview->Add(GUI_PreviewSFML, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL, 5);


	GUI_PanelPreview->SetSizer(GUI_SizerPreview);
	GUI_PanelPreview->Layout();
	GUI_SizerPreview->Fit(GUI_PanelPreview);
	GUI_StatusBar = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);
	GUI_MenuBar = new wxMenuBar(0);
	GUI_MenuFile = new wxMenu();
	wxMenuItem* GUI_MenuFileNew;
	GUI_MenuFileNew = new wxMenuItem(GUI_MenuFile, wxID_ANY, wxString(wxT("New")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuFile->Append(GUI_MenuFileNew);

	wxMenuItem* GUI_MenuFileOpen;
	GUI_MenuFileOpen = new wxMenuItem(GUI_MenuFile, wxID_ANY, wxString(wxT("Open")), wxEmptyString, wxITEM_NORMAL);
	GUI_MenuFile->Append(GUI_MenuFileOpen);

	GUI_MenuBar->Append(GUI_MenuFile, wxT("File"));

	this->SetMenuBar(GUI_MenuBar);


	m_mgr.Update();
	this->Centre(wxBOTH);

	// Connect Events
	GUI_PosX->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::UI_TextCheckNumber), NULL, this);
	GUI_PosY->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::UI_TextCheckNumber), NULL, this);
	GUI_PosZ->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::UI_TextCheckNumber), NULL, this);
}

GUI_MainFrame::~GUI_MainFrame()
{
	// Disconnect Events
	GUI_PosX->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::UI_TextCheckNumber), NULL, this);
	GUI_PosY->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::UI_TextCheckNumber), NULL, this);
	GUI_PosZ->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(GUI_MainFrame::UI_TextCheckNumber), NULL, this);

	m_mgr.UnInit();

}
