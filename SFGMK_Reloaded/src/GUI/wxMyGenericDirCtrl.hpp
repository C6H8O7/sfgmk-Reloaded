#ifndef SFGMKR_WXMYGENERICDIRCTRL_HPP
#define SFGMKR_WXMYGENERICDIRCTRL_HPP

class wxMyGenericDirCtrl : public wxGenericDirCtrl
{
public:
	wxMyGenericDirCtrl(wxWindow *parent, const wxWindowID id = wxID_ANY,
		const wxString &dir = wxDirDialogDefaultFolderStr,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDIRCTRL_3D_INTERNAL,
		const wxString& filter = wxEmptyString,
		int defaultFilter = 0,
		const wxString& name = wxTreeCtrlNameStr)

		: m_root(getDataPath()), wxGenericDirCtrl(parent, id, dir, pos, size, style, filter, defaultFilter, name)
	{
		
	}

	wxString getDataPath()
	{
		std::string path = std::string(wxGetCwd().c_str());

		std::string path_up = path.substr(0, path.find_last_of('\\'));

		std::string path_data = path_up + "\\data";

		return wxString(path_data);
	}

	virtual void SetupSections()
	{
		if (m_root.IsEmpty()) {
			wxGenericDirCtrl::SetupSections();
		}
		else {
			AddSection(m_root, wxFileNameFromPath(m_root), wxFileIconsTable::folder_open);
		}
	}

private:
	wxString m_root;
};


#endif