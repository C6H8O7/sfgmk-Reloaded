#ifndef SFGMKR_WXBUTTONPROPERTY_HPP
#define SFGMKR_WXBUTTONPROPERTY_HPP

class wxButtonMover : public wxPGCellRenderer {
public:
	// pointer to the button from the property
	wxButtonMover(wxButton* btn) : _btn(btn) {}
protected:
	virtual bool Render(wxDC &dc, const wxRect &rect,
		const wxPropertyGrid *propertyGrid, wxPGProperty *property,
		int column, int item, int flags) const {
		if (column == 0) { // 0 = label, 1 = value
						   // instead of actually drawing the cell,
						   // move the button to the cell position:
			wxRect rc(rect);
			// calculate the full property width
			rc.SetWidth(propertyGrid->GetClientRect().width - rect.GetX());
			_btn->SetSize(rc); // move button
			_btn->Show(); // initially hidden, show once 'rendered' (moved)
		}
		return true;
	}
private:
	wxButton* _btn;
};

class wxButtonProperty : public wxPGProperty {
public:
	// [parent] should be the property grid
	// [func] is the event handler
	// [button] is the button label
	// [label] is the property display name (sort name with autosort)
	// [name] is the internal property name
	wxButtonProperty(wxWindow* parent, wxEvtHandler* _handler, wxObjectEventFunction func,
		const wxString& button, const wxString& label = wxPG_LABEL,
		const wxString& name = wxPG_LABEL)
		: wxPGProperty(label, name), _btn(new wxButton(parent, wxID_ANY, button)),
		_renderer(_btn) {
		// connect the handler to the button
		_btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED, func, 0, _handler);
		//_btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED, func);
		_btn->Hide(); // when it's off the grid, it's not rendered 
					  // (thus not moved properly)
	}

	~wxButtonProperty() {
		delete _btn;
	}

protected:
	virtual wxPGCellRenderer* GetCellRenderer(int column) const {
		return &_renderer; // return button mover
	}
	virtual const wxPGEditor* DoGetEditorClass() const {
		return 0; // not using an editor
	}
private:
	wxButton* _btn; // the button attached to the property
	mutable wxButtonMover _renderer; // the button mover
};

#endif