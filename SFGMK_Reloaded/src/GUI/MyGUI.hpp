#ifndef MYGUI_HPP
#define MYGUI_HPP

class MyGUI : public GUI_MainFrame
{
public:

	MyGUI(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SFGMK Reloaded"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1280, 720), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL)
		: GUI_MainFrame(parent, id, title, pos, size, style)
	{
		wxTreeItemId treeid = GUI_HierarchyTree->AddRoot("Scene");

		GUI_HierarchyTree->AppendItem(treeid, "node1");
		GUI_HierarchyTree->AppendItem(treeid, "node2");
		GUI_HierarchyTree->AppendItem(treeid, "node3");
	}

	virtual void GUI_PanelPreview_OnSize(wxSizeEvent& _event)
	{
		int w = GUI_PanelPreview->GetSize().GetWidth();
		int h = GUI_PanelPreview->GetSize().GetHeight();

		float fw = w / 1280.0f;
		float fh = h / 720.0f;

		float f = fw > fh ? fh : fw;

		w = f * 1280.0f;
		h = f * 720.0f;

		GUI_PreviewSFML->SetSize(_event.GetSize());

		GUI_PreviewSFML->setSize(sf::Vector2u(w, h));
	}

	virtual void GUI_MenuGameObjectCreateEmpty_OnMenuSelection(wxCommandEvent& _event)
	{
		printf("adding gameobject\n");
	}
};

#endif