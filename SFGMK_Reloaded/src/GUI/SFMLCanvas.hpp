#ifndef SFGMKR_SFMLCANVAS_HPP
#define SFGMKR_SFMLCANVAS_HPP

#define SFGMKR_DEFAULT_SFML_SIZE_X 1280.0f
#define SFGMKR_DEFAULT_SFML_SIZE_Y 720.0f

class SFMLCanvas : 
	public sf::RenderWindow
#ifdef SFGMKR_EDITOR
	,public wxPanel
#endif
{
public:

#ifdef SFGMKR_EDITOR
	SFMLCanvas(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0);
#else
	SFMLCanvas();
#endif

	virtual ~SFMLCanvas();

	virtual r_void OnUpdate();

	static r_bool isPlaying;

	gmk::InputManager* getInputManager();

	virtual r_bool isEditor();

	static SFMLCanvas* gameCanvas;
	static SFMLCanvas* editorCanvas;
	static Project* project;

private:

#ifdef SFGMKR_EDITOR
	DECLARE_EVENT_TABLE()
	virtual r_void OnIdle(wxIdleEvent&);
	virtual r_void OnPaint(wxPaintEvent&);
	virtual r_void OnEraseBackground(wxEraseEvent&);
#endif

	r_float m_fWidth, m_fHeight;

	gmk::InputManager* m_InputManager;
};

#endif