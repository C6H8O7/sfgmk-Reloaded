#include "stdafx.h"

#ifdef SFGMKR_EDITOR
SFMLCanvas::SFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style)
	: wxPanel(Parent, Id, Position, Size, Style)
{
	m_fWidth = SFGMKR_DEFAULT_SFML_SIZE_X;
	m_fHeight = SFGMKR_DEFAULT_SFML_SIZE_Y;

	create((r_uint32)m_fWidth, (r_uint32)m_fHeight);
	window.create((sf::WindowHandle)GetHandle());
	
	sf::View view;
	view.setSize(r_vector2f((r_float)m_fWidth, (r_float)m_fHeight));
	view.setCenter(r_vector2f(m_fWidth * 0.5f, m_fHeight * 0.5f));

	window.setSize(sf::Vector2u(m_fWidth, m_fHeight));
	window.setView(view);

	m_InputManager = new gmk::InputManager(this);

	ComponentsBank::GetSingleton()->registerAllComponents();
}
#endif

#ifndef SFGMKR_EDITOR
SFMLCanvas::SFMLCanvas()
{
	m_fWidth = SFGMKR_DEFAULT_SFML_SIZE_X;
	m_fHeight = SFGMKR_DEFAULT_SFML_SIZE_Y;

#ifndef SFGMKR_ANDROID
	window.create(sf::VideoMode((r_uint32)m_fWidth, (r_uint32)m_fHeight), "SFGMK Reloaded");
#else
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	window.create(sf::VideoMode::getDesktopMode(), "SFGMK Reloaded", sf::Style::Fullscreen);
#endif

	create((r_uint32)m_fWidth, (r_uint32)m_fHeight);

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
	// On g�n�re un rafra�chissement du contr�le, afin d'assurer un framerate maximum
	Refresh(false);
}

r_void SFMLCanvas::OnPaint(wxPaintEvent& _event)
{
	// On pr�pare le contr�le � �tre dessin�
	wxPaintDC dc(this);

	// On laisse la classe d�riv�e se mettre � jour et dessiner dans le contr�le
	OnUpdate();

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
		if (!gameobjects[i]->networkProp)
			gameobjects[i]->update(this);

	// Post update
	gmk::PhysicManager::getSingleton()->update();

	if(isPlaying)
		gmk::SteeringManager::GetSingleton()->update();

	if (isPlaying)
		gmk::net::NetworkManager::GetInstance()->update();

	// Rendering
	for (r_uint32 i = 0; i < gameobjects.size(); i++)
		gameobjects[i]->draw(this);

	display();

	window.clear(sf::Color(0, 128, 128));
	window.draw(sf::Sprite(getTexture()));
	window.display();

	// Update project
	project->update();
}

gmk::InputManager* SFMLCanvas::getInputManager()
{
	return m_InputManager;
}

r_bool SFMLCanvas::isEditor()
{
	return false;
}
	
SFMLCanvas* SFMLCanvas::gameCanvas = 0;
SFMLCanvas* SFMLCanvas::editorCanvas = 0;
Project* SFMLCanvas::project = 0;