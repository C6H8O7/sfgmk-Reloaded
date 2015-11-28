#ifndef MYGUI_HPP
#define MYGUI_HPP

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

	virtual void GUI_MenuGameObjectCreateEmpty_OnMenuSelection(wxCommandEvent& _event);

	virtual void GUI_PropertyRefresh_OnButtonClick(wxCommandEvent& _event);
	virtual void GUI_PropertyGrid_OnPropertyGridChanged(wxPropertyGridEvent& _event);

	virtual void GUI_MenuComponentSubRenderSprite_OnMenuSelection(wxCommandEvent& _event);
	virtual void GUI_MenuComponentScript_OnMenuSelection(wxCommandEvent& _event);

	static void SetGUI(MyGUI* _gui);
	static MyGUI* GetGUI();

	GameObject* selectedGameObject;

private:

	static MyGUI* gui;
};

#endif