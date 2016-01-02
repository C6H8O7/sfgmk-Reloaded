#ifdef SFGMKR_EDITOR

#ifndef SFGMKR_SFMLEDITORCANVAS_HPP
#define SFGMKR_SFMLEDITORCANVAS_HPP

class SFMLEditorCanvas : public SFMLCanvas
{
	friend class MyGUI;

public:

	SFMLEditorCanvas(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0);

	virtual ~SFMLEditorCanvas();

	virtual r_bool isEditor();

private:

	sf::Texture m_TextureGrid;
	sf::Sprite m_SpriteGrid;

	r_vector2f m_BasicDragPosMouseBegin;

	r_vector2f m_BasicDragPosTransformBegin;
	virtual r_void OnEditionBasicDragPos();

	r_vector2f m_BasicDragPosCameraBegin;
	virtual r_void OnEditionBasicDragCamera();

	r_float m_Zoom;
	r_float m_DefaultWidth, m_DefaultHeight;
	virtual r_void OnEditionBasicZoomCamera();

	virtual r_void OnEditionDrawGrid();

	virtual r_void OnUpdate();

	virtual r_void OnPaint(wxPaintEvent&);
};

#endif

#endif