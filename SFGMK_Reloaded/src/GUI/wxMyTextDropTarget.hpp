#ifdef SFGMKR_EDITOR

#ifndef SFGMKR_WXMYTEXTDROPTARGET_HPP
#define SFGMKR_WXMYTEXTDROPTARGET_HPP

class wxMyTextDropTargetProperties : public wxTextDropTarget
{
public:
	wxMyTextDropTargetProperties(wxPropertyGrid* _owner);

	virtual bool OnDropText(wxCoord _x, wxCoord _y, const wxString& _data);

	wxPropertyGrid *owner;
};

class wxMyTextDropTargetEditor : public wxTextDropTarget
{
public:
	wxMyTextDropTargetEditor(SFMLEditorCanvas* _owner);

	virtual bool OnDropText(wxCoord _x, wxCoord _y, const wxString& _data);

	SFMLEditorCanvas *owner;
};

#endif

#endif