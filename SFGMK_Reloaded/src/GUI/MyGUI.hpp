#ifndef MYGUI_HPP
#define MYGUI_HPP

class MyGUI : public GUI_MainFrame
{
public:

	MyGUI(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SFGMK Reloaded"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1280, 720), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	virtual void GUI_PanelPreview_OnSize(wxSizeEvent& _event);

	void Update_HierarchyTree();
	virtual void GUI_HierarchyTree_OnTreeEndLabelEdit(wxTreeEvent& _event);
	virtual void GUI_HierarchyTree_OnTreeSelChanged(wxTreeEvent& _event);

	virtual void GUI_MenuGameObjectCreateEmpty_OnMenuSelection(wxCommandEvent& _event);

	virtual void GUI_PosX_OnText(wxCommandEvent& _event);
	virtual void GUI_PosY_OnText(wxCommandEvent& _event);
	virtual void GUI_ScaleX_OnText(wxCommandEvent& _event);
	virtual void GUI_ScaleY_OnText(wxCommandEvent& _event);
	virtual void GUI_Rotation_OnText(wxCommandEvent& _event);

	GameObject* selectedGameObject;
};

#endif