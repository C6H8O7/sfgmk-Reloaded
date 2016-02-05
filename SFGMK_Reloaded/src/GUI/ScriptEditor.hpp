#ifdef SFGMKR_EDITOR

#ifndef SFGMKR_SCRIPTEDITOR_HPP
#define SFGMKR_SCRIPTEDITOR_HPP

#include "stdafx.h"

class ScriptEditor
{
public:

	struct sSCRIPT
	{
		r_string name;
		r_string path;
		r_string src;
	};

	static ScriptEditor* GetSingleton();

	r_void init(wxAuiManager* _auiManager, wxWindow* _window, wxStyledTextCtrl* _editor, wxSpinButton* _spin, wxStaticText* _page, wxStaticText* _name);

	r_void update();

	r_void charAdded(wxStyledTextEvent& _event);
	r_void spin(wxSpinEvent& _event);
	r_void save(wxCommandEvent& _event);
	r_void close(wxCommandEvent& _event);

	r_void open(r_string _path);
	r_void toggleView();
	r_void show(r_bool _show);

	r_void changeSelection(r_int32 _prev, r_int32 _new);

	r_string getPreviousWord();

private:

	r_int32 m_selection;

	wxAuiManager* m_mgr;
	wxWindow* m_window;

	wxStyledTextCtrl* m_editor;
	wxSpinButton* m_spin;
	wxStaticText* m_page;
	wxStaticText* m_name;

	gmk::vector<sSCRIPT*> m_scripts;

	ScriptEditor();
	~ScriptEditor();
};

#endif

#endif