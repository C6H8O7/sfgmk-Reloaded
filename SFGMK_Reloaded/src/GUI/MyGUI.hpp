#include "stdafx.h"

#ifdef SFGMKR_EDITOR

#ifndef MYGUI_HPP
#define MYGUI_HPP

class MyGUI : public GUI_MainFrame
{
public:

	struct sGUI_COMPONENT
	{
		r_string path;
		r_bool isPath;
		r_string name;
		r_string type;
		wxMenuItem* item;
		wxMenu* menu;
		wxVariant* userData;
	};

	MyGUI(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SFGMK Reloaded"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1280, 720), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~MyGUI();

	r_void Empty_PropertyGrid();
	r_void Update_PropertyGrid();
	r_void Update_HierarchyTree();
	r_void AddTo_HierarchyTree(GameObject* _gameobject);
	r_void RemoveFrom_HierarchyTree(GameObject* _gameobject);

	virtual r_void GUI_MainFrame_OnKeyDown(wxKeyEvent& _event);

	virtual r_void GUI_PanelEditor_OnSize(wxSizeEvent& _event);
	virtual r_void GUI_PanelPreview_OnSize(wxSizeEvent& _event);

	virtual r_void GUI_HierarchyTree_OnTreeBeginDrag(wxTreeEvent& _event);
	virtual r_void GUI_HierarchyTree_OnTreeEndDrag(wxTreeEvent& _event);
	virtual r_void GUI_HierarchyTree_OnTreeSelChanged(wxTreeEvent& _event);
	virtual r_void GUI_HierarchyTreeMenuRemove_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_HierarchyTreeMenuMoveUp_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_HierarchyTreeMenuMoveDown_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_HierarchyTreeMenuDuplicate_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_HierarchyTree_OnTreeItemActivated(wxTreeEvent& _event);

	virtual r_void GUI_AssetsRefresh_OnButtonClick(wxCommandEvent& _event);
	virtual r_void GUI_AssetsOpen_OnButtonClick(wxCommandEvent& _event);
	virtual r_void GUI_AssetsDirCtrl_OnBeginDrag(wxTreeEvent& _event);
	virtual r_void GUI_AssetsDirCtrlMenuAdd_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_AssetsDirCtrl_OnFileActivation(wxTreeEvent& _event);

	virtual r_void GUI_MenuGameObjectCreateEmpty_OnMenuSelection(wxCommandEvent& _event);

	virtual r_void GUI_PropertyRefresh_OnButtonClick(wxCommandEvent& _event);
	virtual r_void GUI_PropertyGrid_OnPropertyGridChanged(wxPropertyGridEvent& _event);
	virtual r_void GUI_PropertyGrid_OnPropertyGridSelected(wxPropertyGridEvent& _event);

	virtual r_void GUI_ProjectProperty_OnPropertyGridChanged(wxPropertyGridEvent& _event);

	virtual r_void GUI_MenuFileNew_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuFileOpen_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuFileSave_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuFileOpenProject_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuFileSaveProject_OnMenuSelection(wxCommandEvent& _event);

	virtual r_void GUI_MenuViewProject_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuViewScriptEditor_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuViewBehaviorTree_OnMenuSelection(wxCommandEvent& _event);

	virtual r_void GUI_MenuGamePlay_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuGameStop_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuGamePause_OnMenuSelection(wxCommandEvent& _event);

	virtual r_void GUI_HierarchyTreeOnContextMenu(wxTreeEvent &_event);
	virtual r_void GUI_AssetsDirCtrlOnContextMenu(wxTreeEvent &_event);

	virtual r_void GUI_ScriptEditor_OnCharAdded(wxStyledTextEvent &_event);
	virtual r_void GUI_ScriptSelSpin_OnSpin(wxSpinEvent& _event);
	virtual r_void GUI_ScriptSave_OnButtonClick(wxCommandEvent& _event);
	virtual r_void GUI_ScriptClose_OnButtonClick(wxCommandEvent& _event);

	r_void addComponentPath(r_string _path);
	r_void addComponent(r_string _path, r_string _type);
	r_void createAndAddComponent(r_string _name);
	r_void cleanComponents();
	r_void GUI_MenuComponentItem_OnMenuSelection(wxCommandEvent& _event);

	static r_void SetGUI(MyGUI* _gui);
	static MyGUI* GetGUI();

	GameObjectComponent* selectedGameObjectComponent;
	GameObject* selectedGameObject;

private:

	static MyGUI* gui;

	gmk::vector<sGUI_COMPONENT*> m_GUIComponents;
};

#endif

#endif