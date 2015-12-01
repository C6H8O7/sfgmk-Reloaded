#ifdef SFGMKR_EDITOR

#ifndef SFGMKR_SFMLEDITORCANVAS_HPP
#define SFGMKR_SFMLEDITORCANVAS_HPP

class SFMLEditorCanvas : public SFMLCanvas
{
	friend class MyGUI;

public:

	SFMLEditorCanvas(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0);

	virtual ~SFMLEditorCanvas();

	virtual bool isEditor();

private:

	sf::Texture m_TextureGrid;
	sf::Sprite m_SpriteGrid;

	sf::Vector2f m_BasicDragPosMouseBegin;

	sf::Vector2f m_BasicDragPosTransformBegin;
	virtual void OnEditionBasicDragPos();

	sf::Vector2f m_BasicDragPosCameraBegin;
	virtual void OnEditionBasicDragCamera();

	float m_Zoom;
	float m_DefaultWidth, m_DefaultHeight;
	virtual void OnEditionBasicZoomCamera();

	virtual void OnEditionDrawGrid();

	virtual void OnUpdate();

	virtual void OnPaint(wxPaintEvent&);
};

#endif

#endif