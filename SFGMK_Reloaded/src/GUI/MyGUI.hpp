#include "stdafx.h"

#ifdef SFGMKR_EDITOR

#ifndef MYGUI_HPP
#define MYGUI_HPP

class MyGUI : public GUI_MainFrame
{
public:

	MyGUI(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SFGMK Reloaded"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1280, 720), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~MyGUI();

	r_void Empty_PropertyGrid();
	r_void Update_PropertyGrid();
	r_void Update_HierarchyTree();

	virtual r_void GUI_PanelEditor_OnSize(wxSizeEvent& _event);
	virtual r_void GUI_PanelPreview_OnSize(wxSizeEvent& _event);

	virtual r_void GUI_HierarchyTree_OnTreeEndLabelEdit(wxTreeEvent& _event);
	virtual r_void GUI_HierarchyTree_OnTreeSelChanged(wxTreeEvent& _event);
	virtual r_void GUI_HierarchyTreeMenuRemove_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_HierarchyTreeMenuMoveUp_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_HierarchyTreeMenuMoveDown_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_HierarchyTreeMenuDuplicate_OnMenuSelection(wxCommandEvent& _event);

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

	virtual r_void GUI_MenuComponentScript_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubRenderSprite_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubRenderCamera_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentParticleSystem_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentTiledMap_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubIAPathfindingMap_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubIAPathfindingAgent_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubIASubSteeringSubBehaviorSeek_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubIASubSteeringAgent_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentPolygon_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubPhysicOBB_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubPhysicSphere_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubPhysicRigidbody_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubDebugSelector_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubRenderText_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubAudioListener_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuComponentSubAudioSoundBuffer_OnMenuSelection(wxCommandEvent& _event);

	virtual r_void GUI_MenuFileNew_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuFileOpen_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuFileSave_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuFileOpenProject_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuFileSaveProject_OnMenuSelection(wxCommandEvent& _event);

	virtual r_void GUI_MenuViewProject_OnMenuSelection(wxCommandEvent& _event);

	virtual r_void GUI_MenuGamePlay_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuGameStop_OnMenuSelection(wxCommandEvent& _event);
	virtual r_void GUI_MenuGamePause_OnMenuSelection(wxCommandEvent& _event);

	virtual r_void GUI_HierarchyTreeOnContextMenu(wxTreeEvent &_event);
	virtual r_void GUI_AssetsDirCtrlOnContextMenu(wxTreeEvent &_event);

	static r_void SetGUI(MyGUI* _gui);
	static MyGUI* GetGUI();

	GameObjectComponent* selectedGameObjectComponent;
	GameObject* selectedGameObject;

private:

	static MyGUI* gui;
};

#endif

#endif