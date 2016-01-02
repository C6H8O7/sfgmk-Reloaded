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
		r_int32 defaultFilter = 0,
		const wxString& name = wxTreeCtrlNameStr)

		: m_root(r_string("")), wxGenericDirCtrl(parent, id, dir, pos, size, style, filter, defaultFilter, name)
	{
		
	}

	~wxMyGenericDirCtrl()
	{

	}

	virtual r_void SetupSections()
	{
		if (!m_root.IsEmpty()) {
			AddSection(m_root, wxFileNameFromPath(m_root), wxFileIconsTable::folder_open);
		}
	}

	r_void SetRoot(r_string _root)
	{
		m_root = wxString(_root.c_str());
	}

private:
	wxString m_root;
};

#endif