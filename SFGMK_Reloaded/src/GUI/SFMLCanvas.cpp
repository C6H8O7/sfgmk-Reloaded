#include "stdafx.h"

#ifdef SFGMKR_EDITOR
SFMLCanvas::SFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style)
	: wxPanel(Parent, Id, Position, Size, Style)
{
	sf::RenderWindow::create(GetHandle());

	m_fWidth = SFGMKR_DEFAULT_SFML_SIZE_X;
	m_fHeight = SFGMKR_DEFAULT_SFML_SIZE_Y;
	
	sf::View view;
	view.setCenter(r_vector2f(m_fWidth / 2.0f, m_fHeight / 2.0f));
	view.setSize(r_vector2f((r_float)m_fWidth, (r_float)m_fHeight));

	sf::RenderWindow::setSize(sf::Vector2u(m_fWidth, m_fHeight));
	sf::RenderWindow::setView(view);

	m_InputManager = new gmk::InputManager(this);

	ComponentsBank::GetSingleton()->registerAllComponents();
}
#endif

#ifndef SFGMKR_EDITOR
SFMLCanvas::SFMLCanvas()
{
#ifndef SFGMKR_ANDROID
	sf::RenderWindow::create(sf::VideoMode((r_uint32)SFGMKR_DEFAULT_SFML_SIZE_X, (r_uint32)SFGMKR_DEFAULT_SFML_SIZE_Y), "SFGMK Reloaded");
#else
	sf::RenderWindow::create(sf::VideoMode((r_uint32)SFGMKR_DEFAULT_SFML_SIZE_X, (r_uint32)SFGMKR_DEFAULT_SFML_SIZE_Y), "SFGMK Reloaded", sf::Style::Fullscreen);
#endif

	m_fWidth = SFGMKR_DEFAULT_SFML_SIZE_X;
	m_fHeight = SFGMKR_DEFAULT_SFML_SIZE_Y;

	sf::View view;
	view.setCenter(r_vector2f(m_fWidth / 2.0f, m_fHeight / 2.0f));
	view.setSize(r_vector2f((r_float)m_fWidth, (r_float)m_fHeight));

	sf::RenderWindow::setSize(sf::Vector2u((r_uint32)m_fWidth, (r_uint32)m_fHeight));
	sf::RenderWindow::setView(view);

	m_InputManager = new gmk::InputManager(this);

	ComponentsBank::GetSingleton()->registerAllComponents();
}
#endif

SFMLCanvas::~SFMLCanvas()
{
	delete m_InputManager;
}

#ifdef SFGMKR_EDITOR
r_void SFMLCanvas::OnIdle(wxIdleEvent& _event)
{
	// On génère un rafraîchissement du contrôle, afin d'assurer un framerate maximum
	Refresh(false);

	_event.RequestMore(true);
}

r_void SFMLCanvas::OnPaint(wxPaintEvent& _event)
{
	// On prépare le contrôle à être dessiné
	wxPaintDC dc(this);

	// On laisse la classe dérivée se mettre à jour et dessiner dans le contrôle
	OnUpdate();

#ifdef SFGMKR_EDITOR
	static r_float timer = 0;
	static sf::Clock clock;

	float dt = clock.restart().asSeconds();
	timer += dt;

	if (timer >= 0.05f)
	{
		timer = 0.0f;

		MyGUI* gui = MyGUI::GetGUI();

		gui->Update_PropertyGrid();

		r_int8 status[50];
		sprintf_s(status, "Updated in: %.2f ms (%d FPS)", dt * 1000.0f, (r_int32)(1.0f / dt));
		gui->GUI_StatusBar->SetStatusText(wxString(status));
	}
#endif
}

r_void SFMLCanvas::OnEraseBackground(wxEraseEvent& _event)
{

}

BEGIN_EVENT_TABLE(SFMLCanvas, wxPanel)
	EVT_IDLE(SFMLCanvas::OnIdle)
	EVT_ERASE_BACKGROUND(SFMLCanvas::OnEraseBackground)
	EVT_PAINT(SFMLCanvas::OnPaint)
END_EVENT_TABLE()
#endif

r_void SFMLCanvas::OnUpdate()
{
	// On efface la vue
	clear(sf::Color(0, 128, 128));

	// Pre update
	gmk::TimeManager::GetSingleton()->update();
	m_InputManager->update();

	// Update gameobjects / components
	gmk::vector<GameObject*>& gameobjects = SFMLCanvas::project->getCurrentScene()->getGameObjects();

	for (r_uint32 i = 0; i < gameobjects.size(); i++)
		gameobjects[i]->update(this);

	for (r_uint32 i = 0; i < gameobjects.size(); i++)
		gameobjects[i]->draw(this);

	// Post update
	gmk::PhysicManager::getSingleton()->update();

	// Update project
	project->update();

	// On affiche tout ça à l'écran
	display();
}

gmk::InputManager* SFMLCanvas::getInputManager()
{
	return m_InputManager;
}

r_bool SFMLCanvas::isEditor()
{
	return false;
}

r_bool SFMLCanvas::isPlaying = false;
	
SFMLCanvas* SFMLCanvas::gameCanvas = 0;
SFMLCanvas* SFMLCanvas::editorCanvas = 0;
Project* SFMLCanvas::project = 0;