///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
class wxSFMLCanvas;

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/treectrl.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUI_MainFrame
///////////////////////////////////////////////////////////////////////////////
class GUI_MainFrame : public wxFrame
{
private:

protected:
	wxScrolledWindow* GUI_PanelProperties;
	wxStaticText* GUI_TextTransform;
	wxStaticText* GUI_TextPosition;
	wxStaticText* GUI_TextX;
	wxTextCtrl* GUI_PosX;
	wxStaticText* GUI_TextY;
	wxTextCtrl* GUI_PosY;
	wxScrolledWindow* GUI_PanelHierarchy;
	wxScrolledWindow* GUI_PanelAssets;
	wxPanel* GUI_PanelEditor;
	wxPanel* GUI_EditorSFML;
	wxPanel* GUI_PanelPreview;
	wxMenuBar* GUI_MenuBar;
	wxMenu* GUI_MenuFile;
	wxMenu* GUI_MenuGameObject;

	// Virtual event handlers, overide them in your derived class
	virtual void GUI_PanelPreview_OnSize(wxSizeEvent& event) { event.Skip(); }
	virtual void GUI_MenuGameObjectCreateEmpty_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }


public:
	wxTreeCtrl* GUI_HierarchyTree;
	wxSFMLCanvas* GUI_PreviewSFML;
	wxString validator_posx;
	wxString validator_posy;

	GUI_MainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SFGMK Reloaded"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1280, 720), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	wxAuiManager m_mgr;

	~GUI_MainFrame();

};

#endif //__GUI_H__
