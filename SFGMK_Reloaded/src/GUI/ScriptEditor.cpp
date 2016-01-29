#include "stdafx.h"

ScriptEditor::ScriptEditor()
{
	m_selection = 0;
}

ScriptEditor::~ScriptEditor()
{

}

ScriptEditor* ScriptEditor::GetSingleton()
{
	static ScriptEditor singleton;
	return &singleton;
}

r_void ScriptEditor::init(wxAuiManager* _auiManager, wxWindow* _window, wxStyledTextCtrl* _editor, wxSpinButton* _spin, wxStaticText* _page, wxStaticText* _name)
{
	m_mgr = _auiManager;
	m_window = _window;

	m_editor = _editor;
	m_spin = _spin;
	m_page = _page;
	m_name = _name;
	
	m_editor->StyleClearAll();

	m_editor->SetLexer(wxSTC_LEX_LUA);

	m_editor->StyleSetForeground(wxSTC_LUA_DEFAULT, wxColor(0, 255, 255));

	m_editor->StyleSetForeground(wxSTC_LUA_COMMENT, wxColor(0, 128, 0));
	m_editor->StyleSetForeground(wxSTC_LUA_COMMENTLINE, wxColor(0, 128, 0));
	m_editor->StyleSetForeground(wxSTC_LUA_COMMENTDOC, wxColor(0, 128, 0));

	m_editor->StyleSetForeground(wxSTC_LUA_NUMBER, wxColor(255, 128, 0));

	m_editor->StyleSetForeground(wxSTC_LUA_STRING, wxColor(255, 0, 0));
	m_editor->StyleSetForeground(wxSTC_LUA_CHARACTER, wxColor(255, 0, 0));
	m_editor->StyleSetForeground(wxSTC_LUA_LITERALSTRING, wxColor(255, 0, 0));

	m_editor->StyleSetForeground(wxSTC_LUA_PREPROCESSOR, wxColor(0, 255, 255));
	m_editor->StyleSetForeground(wxSTC_LUA_IDENTIFIER, wxColor(0, 0, 0));
	m_editor->StyleSetForeground(wxSTC_LUA_STRINGEOL, wxColor(0, 255, 255));

	m_editor->StyleSetForeground(wxSTC_LUA_WORD2, wxColor(0, 255, 255));
	m_editor->StyleSetForeground(wxSTC_LUA_WORD3, wxColor(0, 255, 255));
	m_editor->StyleSetForeground(wxSTC_LUA_WORD4, wxColor(0, 255, 255));
	m_editor->StyleSetForeground(wxSTC_LUA_WORD5, wxColor(0, 255, 255));
	m_editor->StyleSetForeground(wxSTC_LUA_WORD6, wxColor(0, 255, 255));
	m_editor->StyleSetForeground(wxSTC_LUA_WORD7, wxColor(0, 255, 255));
	m_editor->StyleSetForeground(wxSTC_LUA_WORD8, wxColor(0, 255, 255));
	m_editor->StyleSetForeground(wxSTC_LUA_LABEL, wxColor(0, 255, 255));

	m_editor->StyleSetForeground(wxSTC_LUA_WORD, wxColor(0, 0, 255));
	m_editor->StyleSetBold(wxSTC_LUA_WORD, true);
	m_editor->SetKeyWords(0, "and break do else elseif end false for function if in local nil not or repeat return then true until while");

	m_editor->StyleSetForeground(wxSTC_LUA_WORD2, wxColor(128, 58, 255));
	m_editor->StyleSetBold(wxSTC_LUA_WORD2, true);
	m_editor->SetKeyWords(1, "abs acos asin atan atan2 ceil cos deg exp floor format frexp gsub ldexp log log10 max min mod rad random randomseed sin sqrt strbyte strchar strfind strlen strlower strrep strsub strupper tan string.byte string.char string.dump string.find string.len string.lower string.rep string.sub string.upper string.format string.gfind string.gsub table.concat table.foreach table.foreachi table.getn table.sort table.insert table.remove table.setn math.abs math.acos math.asin math.atan math.atan2 math.ceil math.cos math.deg math.exp math.floor math.frexp math.ldexp math.log math.log10 math.max math.min math.mod math.pi math.rad math.random math.randomseed math.sin math.sqrt math.tan");
}

r_void ScriptEditor::charAdded(wxStyledTextEvent& _event)
{
	int charAdded = _event.GetKey();
	int currentPos = m_editor->GetCurrentPos();
	int startPos = m_editor->WordStartPosition(currentPos, true);

	int lenEntered = currentPos - startPos;

	if (charAdded == '.')
	{
		int prevWordStart = m_editor->WordStartPosition(startPos - 1, true);
		int prevWordEnd = m_editor->WordEndPosition(prevWordStart, true);

		int prevWordLen = prevWordEnd - prevWordStart;

		if (prevWordLen)
		{
			wxMemoryBuffer buffer = m_editor->GetStyledText(prevWordStart, prevWordEnd);

			r_string prevWord;
			for (r_uint32 i = 0; i < buffer.GetBufSize(); i += 2)
				prevWord += ((char*)buffer.GetData())[i];

			printf("%s\n", (const char*)prevWord.c_str());
		}
	}

	if (lenEntered > 0)
	{
		m_editor->AutoCompShow(lenEntered, wxString("and break do else elseif end false for function if in local nil not or repeat return then true until while"));
	}
}

r_void ScriptEditor::update()
{
	if (m_scripts.size())
	{
		sSCRIPT* script = m_scripts[m_selection];

		m_editor->SetText(script->src);
		m_name->SetLabel(script->name);
		m_page->SetLabel(std::to_string(m_selection + 1) + " / " + std::to_string(m_scripts.size()));
	}
	else
	{
		m_editor->SetText(wxString(""));
		m_name->SetLabel(wxString(""));
		m_page->SetLabel(wxString("0 / 0"));
	}
}

r_void ScriptEditor::spin(wxSpinEvent& _event)
{
	changeSelection(m_selection, _event.GetPosition());
	update();
}

r_void ScriptEditor::save(wxCommandEvent& _event)
{
	if (m_scripts.size())
	{
		sSCRIPT* script = m_scripts[m_selection];
		script->src = m_editor->GetText();

		FILE* f;
		fopen_s(&f, script->path.c_str(), "wb+");
		fwrite(script->src.c_str(), sizeof(r_int8), script->src.length(), f);
		fclose(f);
	}
}

r_void ScriptEditor::close(wxCommandEvent& _event)
{
	if (m_scripts.size())
	{
		r_int32 prevSel = m_selection;
		changeSelection(m_selection, m_selection - 1);

		delete m_scripts[prevSel];
		m_scripts.erase(prevSel, prevSel);

		update();
	}

	if(m_scripts.size())
		m_spin->SetRange(0, m_scripts.size() - 1);
	else
		m_spin->SetRange(0, 0);
}

r_void ScriptEditor::open(r_string _path)
{
	r_string name = _path.substr(_path.rfind("/") + 1);

	r_bool found = false;

	for (r_uint32 i = 0; i < m_scripts.size(); i++)
	{
		if (name == m_scripts[i]->name)
		{
			changeSelection(m_selection, (r_int32)i);
			found = true;
		}
	}

	if (!found)
	{
		sSCRIPT* script = new sSCRIPT();

		script->name = name;
		script->path = _path;
		script->src = gmk::getFileContent(_path);

		m_spin->SetRange(0, m_scripts.size());
		changeSelection(m_selection, (r_int32)m_scripts.size());

		m_scripts.push_back(script);
	}

	update();
	show(true);
}

r_void ScriptEditor::toggleView()
{
	wxAuiPaneInfo& pane = m_mgr->GetPane(m_window);

	if (pane.IsShown())
		pane.Hide();
	else
		pane.Show();

	m_mgr->Update();
}

r_void ScriptEditor::show(r_bool _show)
{
	wxAuiPaneInfo& pane = m_mgr->GetPane(m_window);

	if (_show)
		pane.Show();
	else
		pane.Hide();

	m_mgr->Update();
}

r_void ScriptEditor::changeSelection(r_int32 _prev, r_int32 _new)
{
	if (_new < 0)
		_new = 0;

	if (m_scripts.size())
		m_scripts[_prev]->src = m_editor->GetText();

	m_selection = _new;
	m_spin->SetValue(_new);
}