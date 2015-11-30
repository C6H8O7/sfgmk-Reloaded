#ifdef SFGMKR_EDITOR

#ifndef MYGUI_HPP
#define MYGUI_HPP

#undef GUI_HierarchyTreeOnContextMenu
#undef GUI_AssetsDirCtrlOnContextMenu
#undef PopupMenu

class MyGUI : public GUI_MainFrame
{
public:

	MyGUI(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SFGMK Reloaded"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1280, 720), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	void Update_PropertyGrid();
	void Update_HierarchyTree();

	virtual void GUI_PanelEditor_OnSize(wxSizeEvent& _event);
	virtual void GUI_PanelPreview_OnSize(wxSizeEvent& _event);

	virtual void GUI_HierarchyTree_OnTreeEndLabelEdit(wxTreeEvent& _event);
	virtual void GUI_HierarchyTree_OnTreeSelChanged(wxTreeEvent& _event);
	virtual void GUI_HierarchyTreeMenuRemove_OnMenuSelection(wxCommandEvent& _event);
	virtual void GUI_HierarchyTreeMenuMoveUp_OnMenuSelection(wxCommandEvent& _event);
	virtual void GUI_HierarchyTreeMenuMoveDown_OnMenuSelection(wxCommandEvent& _event);

	virtual void GUI_AssetsDirCtrl_OnBeginDrag(wxTreeEvent& _event);
	virtual void GUI_AssetsDirCtrlMenuAdd_OnMenuSelection(wxCommandEvent& _event);

	virtual void GUI_MenuGameObjectCreateEmpty_OnMenuSelection(wxCommandEvent& _event);

	virtual void GUI_PropertyRefresh_OnButtonClick(wxCommandEvent& _event);
	virtual void GUI_PropertyGrid_OnPropertyGridChanged(wxPropertyGridEvent& _event);

	virtual void GUI_MenuComponentScript_OnMenuSelection(wxCommandEvent& _event);
	virtual void GUI_MenuComponentSubRenderSprite_OnMenuSelection(wxCommandEvent& _event);
	virtual void GUI_MenuComponentSubRenderCamera_OnMenuSelection(wxCommandEvent& _event);

	virtual void GUI_MenuFileOpen_OnMenuSelection(wxCommandEvent& _event);
	virtual void GUI_MenuFileSave_OnMenuSelection(wxCommandEvent& _event);

	virtual void GUI_MenuGamePlay_OnMenuSelection(wxCommandEvent& _event);
	virtual void GUI_MenuGameStop_OnMenuSelection(wxCommandEvent& _event);
	virtual void GUI_MenuGamePause_OnMenuSelection(wxCommandEvent& _event);

	virtual void GUI_HierarchyTreeOnContextMenu(wxTreeEvent &_event);
	virtual void GUI_AssetsDirCtrlOnContextMenu(wxTreeEvent &_event);

	static void SetGUI(MyGUI* _gui);
	static MyGUI* GetGUI();

	GameObject* selectedGameObject;

private:

	static MyGUI* gui;
};

#endif

#endif