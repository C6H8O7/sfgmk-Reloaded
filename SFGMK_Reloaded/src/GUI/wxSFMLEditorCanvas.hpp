#ifndef SFGMKR_WXSFMLEDITORCANVAS_HPP
#define SFGMKR_WXSFMLEDITORCANVAS_HPP

class wxSFMLEditorCanvas : public wxSFMLCanvas
{
public:

	wxSFMLEditorCanvas(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0);

	virtual ~wxSFMLEditorCanvas();

private:

	sf::Vector2f m_BasicDragPosMouseBegin;
	sf::Vector2f m_BasicDragPosTransformBegin;
	virtual void OnEditionBasicDragPos();

	virtual void OnUpdate();

	virtual void OnPaint(wxPaintEvent&);
};

#endif