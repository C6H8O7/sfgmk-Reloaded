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
#endif

#ifndef SFGMKR_EDITOR
	SFMLCanvas();
#endif

	virtual ~SFMLCanvas();

	virtual void OnUpdate();

	static bool isPlaying;

	sfgmk::InputManager* getInputManager();

	virtual bool isEditor();

private:

#ifdef SFGMKR_EDITOR
	DECLARE_EVENT_TABLE()
	virtual void OnIdle(wxIdleEvent&);
	virtual void OnPaint(wxPaintEvent&);
	virtual void OnEraseBackground(wxEraseEvent&);
#endif

	float m_fWidth, m_fHeight;

	sfgmk::InputManager* m_InputManager;
};

#endif