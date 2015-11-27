#ifndef SFGMKR_WXSFMLCANVAS_HPP
#define SFGMKR_WXSFMLCANVAS_HPP

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

	virtual void OnIdle(wxIdleEvent&);
	virtual void OnPaint(wxPaintEvent&);
	virtual void OnEraseBackground(wxEraseEvent&);

	float m_fWidth, m_fHeight;

	sfgmk::TimeManager* m_TimeManager;
	sfgmk::InputManager* m_InputManager;
};

#endif