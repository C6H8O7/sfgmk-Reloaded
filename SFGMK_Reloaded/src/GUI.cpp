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

	GUI_PanelProperties = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_mgr.AddPane(GUI_PanelProperties, wxAuiPaneInfo().Right().Caption(wxT("Propeties")).CloseButton(false).Dock().Resizable().FloatingSize(wxSize(100, 59)).MinSize(wxSize(100, -1)).Layer(7));

	wxBoxSizer* GUI_SizerProperties;
	GUI_SizerProperties = new wxBoxSizer(wxVERTICAL);


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
	m_mgr.AddPane(GUI_PanelHierarchy, wxAuiPaneInfo().Right().Caption(wxT("Hierarchy")).CloseButton(false).Dock().Resizable().FloatingSize(wxSize(100, 59)).MinSize(wxSize(100, -1)).Layer(5));

	wxBoxSizer* GUI_SizerHierarchy;
	GUI_SizerHierarchy = new wxBoxSizer(wxVERTICAL);


	GUI_PanelHierarchy->SetSizer(GUI_SizerHierarchy);
	GUI_PanelHierarchy->Layout();
	GUI_SizerHierarchy->Fit(GUI_PanelHierarchy);
	GUI_PanelEditor = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_mgr.AddPane(GUI_PanelEditor, wxAuiPaneInfo().Center().Caption(wxT("Editor")).CloseButton(false).MaximizeButton(true).Dock().Resizable().FloatingSize(wxSize(-1, -1)));

	wxBoxSizer* GUI_SizerEditor;
	GUI_SizerEditor = new wxBoxSizer(wxVERTICAL);

	GUI_EditorSFML = new wxSFMLCanvas(GUI_PanelEditor, wxID_ANY, wxPoint(-1, -1), wxSize(1280, 720), wxTAB_TRAVERSAL);
	GUI_SizerEditor->Add(GUI_EditorSFML, 1, wxEXPAND | wxALL, 5);


	GUI_PanelEditor->SetSizer(GUI_SizerEditor);
	GUI_PanelEditor->Layout();
	GUI_SizerEditor->Fit(GUI_PanelEditor);
	GUI_PanelPreview = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_mgr.AddPane(GUI_PanelPreview, wxAuiPaneInfo().Center().Caption(wxT("Preview")).CloseButton(false).MaximizeButton(true).Dock().Resizable().FloatingSize(wxDefaultSize));

	wxBoxSizer* GUI_SizerPreview;
	GUI_SizerPreview = new wxBoxSizer(wxVERTICAL);


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
}

GUI_MainFrame::~GUI_MainFrame()
{
	m_mgr.UnInit();

}
