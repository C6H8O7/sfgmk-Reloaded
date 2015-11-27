#ifndef WXSFMLCANVAS_HPP
#define WXSFMLCANVAS_HPP

#define SFGMKR_DEFAULT_SFML_SIZE_X 1280.0f
#define SFGMKR_DEFAULT_SFML_SIZE_Y 720.0f

class wxSFMLCanvas : public wxPanel, public sf::RenderWindow
{
public:

	wxSFMLCanvas(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0);

	virtual ~wxSFMLCanvas();

private:

	DECLARE_EVENT_TABLE()

	virtual void OnUpdate();

	void OnIdle(wxIdleEvent&);

	void OnPaint(wxPaintEvent&);

	void OnEraseBackground(wxEraseEvent&);

	float m_fWidth, m_fHeight;
};

#endif