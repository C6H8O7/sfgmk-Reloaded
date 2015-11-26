#ifndef MYGUI_HPP
#define MYGUI_HPP

class MyGUI : public GUI_MainFrame
{
public:

	MyGUI(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SFGMK Reloaded"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1280, 720), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL)
		: GUI_MainFrame(parent, id, title, pos, size, style)
	{

	}

	virtual void UI_TextCheckNumber(wxCommandEvent& event)
	{

	}
};

#endif