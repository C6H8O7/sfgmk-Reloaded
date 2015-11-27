#ifndef SFGMKR_WXSFMLEDITORCANVAS_HPP
#define SFGMKR_WXSFMLEDITORCANVAS_HPP

class wxSFMLEditorCanvas : public wxSFMLCanvas
{
public:

	wxSFMLEditorCanvas(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0);

	virtual ~wxSFMLEditorCanvas();

private:

	sf::Texture m_TextureGrid;
	sf::Sprite m_SpriteGrid;

	sf::Vector2f m_BasicDragPosMouseBegin;

	sf::Vector2f m_BasicDragPosTransformBegin;
	virtual void OnEditionBasicDragPos();

	sf::Vector2f m_BasicDragPosCameraBegin;
	virtual void OnEditionBasicDragCamera();

	float m_Zoom;
	virtual void OnEditionBasicZoomCamera();

	virtual void OnEditionDrawGrid();

	virtual void OnUpdate();

	virtual void OnPaint(wxPaintEvent&);
};

#endif