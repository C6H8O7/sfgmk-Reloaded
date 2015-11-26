#ifndef WXSFMLCANVAS_HPP
#define WXSFMLCANVAS_HPP

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

	sf::Sprite sprite;
	sf::Texture texture;

	float m_fWidth, m_fHeight;
};

#endif