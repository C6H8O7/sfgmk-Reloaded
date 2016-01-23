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
class SFMLCanvas;
class SFMLEditorCanvas;
class wxMyGenericDirCtrl;

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/treectrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/dirctrl.h>
#include <wx/button.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUI_MainFrame
///////////////////////////////////////////////////////////////////////////////
class GUI_MainFrame : public wxFrame
{
private:
	wxPGProperty* GUI_ProjectPropertyHeight;

protected:
	wxScrolledWindow* GUI_PanelHierarchy;
	wxMenu* GUI_HierarchyTreeMenu;
	wxScrolledWindow* GUI_PanelAssets;
	wxMyGenericDirCtrl* GUI_AssetsDirCtrl;
	wxMenu* GUI_AssetsDirCtrlMenu;
	wxButton* GUI_AssetsOpen;
	wxButton* GUI_AssetsRefresh;
	wxScrolledWindow* GUI_PanelProperties;
	wxButton* GUI_PropertyRefresh;
	wxPanel* GUI_PanelEditor;
	wxPanel* GUI_PanelPreview;
	wxMenuBar* GUI_MenuBar;
	wxMenu* GUI_MenuFile;
	wxMenu* GUI_MenuView;
	wxMenu* GUI_MenuGameObject;
	wxMenu* GUI_MenuComponent;
	wxMenu* GUI_MenuComponentSubRender;
	wxMenu* GUI_MenuComponentSubIA;
	wxMenu* GUI_MenuComponentSubIASubSteering;
	wxMenu* GUI_MenuComponentSubIASubSteeringSubBehavior;
	wxMenu* GUI_MenuComponentSubPhysic;
	wxMenu* GUI_MenuComponentSubDebug;
	wxMenu* GUI_MenuComponentSubAudio;
	wxMenu* GUI_MenuGame;
	wxScrolledWindow* GUI_PanelProject;
	wxPGProperty* GUI_ProjectPropertyCategory;

	// Virtual event handlers, overide them in your derived class
	virtual void GUI_HierarchyTree_OnTreeEndLabelEdit(wxTreeEvent& event) { event.Skip(); }
	virtual void GUI_HierarchyTree_OnTreeSelChanged(wxTreeEvent& event) { event.Skip(); }
	virtual void GUI_HierarchyTreeMenuRemove_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_HierarchyTreeMenuMoveUp_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_HierarchyTreeMenuMoveDown_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_HierarchyTreeMenuDuplicate_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_AssetsDirCtrl_OnBeginDrag(wxTreeEvent& event) { event.Skip(); }
	virtual void GUI_AssetsDirCtrlMenuAdd_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_AssetsOpen_OnButtonClick(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_AssetsRefresh_OnButtonClick(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_PropertyRefresh_OnButtonClick(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_PropertyGrid_OnPropertyGridChanged(wxPropertyGridEvent& event) { event.Skip(); }
	virtual void GUI_PanelEditor_OnSize(wxSizeEvent& event) { event.Skip(); }
	virtual void GUI_PanelPreview_OnSize(wxSizeEvent& event) { event.Skip(); }
	virtual void GUI_MenuFileNew_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuFileOpen_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuFileSave_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuFileOpenProject_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuFileSaveProject_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuViewProject_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuGameObjectCreateEmpty_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubRenderSprite_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubRenderCamera_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubRenderText_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubIASubSteeringSubBehaviorSeek_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubIASubSteeringAgent_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubIAPathfindingMap_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubIAPathfindingAgent_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubPhysicOBB_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubPhysicSphere_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubPhysicRigidbody_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubDebugSelector_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubAudioListener_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentSubAudioSoundBuffer_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentScript_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentParticleSystem_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentTiledMap_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuComponentPolygon_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuGamePlay_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuGameStop_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_MenuGamePause_OnMenuSelection(wxCommandEvent& event) { event.Skip(); }
	virtual void GUI_ProjectProperty_OnPropertyGridChanged(wxPropertyGridEvent& event) { event.Skip(); }


public:
	wxTreeCtrl* GUI_HierarchyTree;
	wxPropertyGrid* GUI_PropertyGrid;
	SFMLEditorCanvas* GUI_EditorSFML;
	SFMLCanvas* GUI_PreviewSFML;
	wxStatusBar* GUI_StatusBar;
	wxPropertyGrid* GUI_ProjectProperty;
	wxPGProperty* GUI_ProjectPropertyPath;
	wxPGProperty* GUI_ProjectPropertyName;
	wxPGProperty* GUI_ProjectPropertyWidth;

	GUI_MainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SFGMK Reloaded"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1280, 720), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	wxAuiManager m_mgr;

	~GUI_MainFrame();

	void GUI_HierarchyTreeOnContextMenu(wxMouseEvent &event)
	{
		GUI_HierarchyTree->PopupMenu(GUI_HierarchyTreeMenu, event.GetPosition());
	}

	void GUI_AssetsDirCtrlOnContextMenu(wxMouseEvent &event)
	{
		GUI_AssetsDirCtrl->PopupMenu(GUI_AssetsDirCtrlMenu, event.GetPosition());
	}

};

#endif //__GUI_H__
