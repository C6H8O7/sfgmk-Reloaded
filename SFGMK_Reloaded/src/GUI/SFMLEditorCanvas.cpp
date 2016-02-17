#include "stdafx.h"

#ifdef SFGMKR_EDITOR

SFMLEditorCanvas::SFMLEditorCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style)
	: SFMLCanvas(Parent, Id, Position, Size, Style)
{
	m_TextureGrid.loadFromFile("../data/editor/grid.png");

	m_SpriteGrid.setTexture(m_TextureGrid);
}

SFMLEditorCanvas::~SFMLEditorCanvas()
{

}

r_bool SFMLEditorCanvas::isEditor()
{
	return true;
}

r_void SFMLEditorCanvas::OnPaint(wxPaintEvent& _event)
{
	// On prépare le contrôle à être dessiné
	wxPaintDC dc(this);

	// On efface la vue
	clear(sf::Color(128, 128, 128));

	// Pre loop
	m_InputManager->update();

	// On laisse la classe dérivée se mettre à jour et dessiner dans le contrôle
	OnUpdate();

	// On affiche tout ça à l'écran
	display();

	window.clear(sf::Color(128, 128, 128));
	window.draw(sf::Sprite(getTexture()));
	window.display();
}

r_void SFMLEditorCanvas::OnEditionBasicDragPos()
{
	MyGUI* gui = MyGUI::GetGUI();

	GameObject *gameobject = gui->selectedGameObject;

	if (gameobject)
	{
		gmk::Mouse& mouse = m_InputManager->getMouse();

		r_int32 state = mouse.getButtonState(sf::Mouse::Left);

		if (state == KEY_PRESSED)
		{
			m_BasicDragPosMouseBegin = mouse.getWorldPosition();
			m_BasicDragPosTransformBegin = gameobject->transform.getPosition();
		}
		else if (state == KEY_DOWN)
		{
			r_vector2f diff = mouse.getWorldPosition() - m_BasicDragPosMouseBegin;
			gameobject->transform.setPosition(m_BasicDragPosTransformBegin + diff);
		}
	}
}

r_void SFMLEditorCanvas::OnEditionBasicDragCamera()
{
	sf::View view = getView();

	gmk::Mouse& mouse = m_InputManager->getMouse();

	r_int32 state = mouse.getButtonState(sf::Mouse::Middle);

	if (state == KEY_PRESSED)
	{
		m_BasicDragPosMouseBegin = r_vector2f(mouse.getWindowPosition());
		m_BasicDragPosCameraBegin = view.getCenter();
	}
	else if (state == KEY_DOWN)
	{
		r_vector2f diff = r_vector2f(mouse.getWindowPosition()) - m_BasicDragPosMouseBegin;

		view.setCenter(m_BasicDragPosCameraBegin - diff);
		setView(view);
	}
}

r_void SFMLEditorCanvas::OnEditionBasicZoomCamera()
{
	sf::View view = getView();

	gmk::Mouse& mouse = m_InputManager->getMouse();

	r_int32 tick = mouse.getWheelState();

	if (tick)
	{
		view.zoom(1 - tick * 0.1f);
		setView(view);
	}
}

r_void SFMLEditorCanvas::OnEditionDrawGrid()
{
	for (r_int32 x = -1; x < 6; x++)
	{
		for (r_int32 y = -1; y < 4; y++)
		{
			m_SpriteGrid.setPosition(x * 256.0f, y * 256.0f);
			draw(m_SpriteGrid);
		}
	}
}

r_void SFMLEditorCanvas::OnUpdate()
{
	OnEditionBasicDragPos();
	OnEditionBasicDragCamera();
	OnEditionBasicZoomCamera();

	OnEditionDrawGrid();

	MyGUI* gui = MyGUI::GetGUI();

	if(gui->selectedGameObjectComponent)
		gui->selectedGameObjectComponent->OnEditorUpdate();

	gmk::vector<GameObject*>& gameobjects = SFMLCanvas::project->getCurrentScene()->getGameObjects();

	for (r_uint32 i = 0; i < gameobjects.size(); i++)
		gameobjects[i]->draw(this);
}

#endif