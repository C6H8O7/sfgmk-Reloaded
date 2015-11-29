#ifdef SFGMKR_EDITOR
SFMLCanvas::SFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style)
	: wxPanel(Parent, Id, Position, Size, Style)
{
	// Testé sous Windows XP seulement (devrait fonctionner sous X11 et
	// les autres versions de Windows - aucune idée concernant MacOS)
	sf::RenderWindow::create(GetHandle());

	m_fWidth = SFGMKR_DEFAULT_SFML_SIZE_X;
	m_fHeight = SFGMKR_DEFAULT_SFML_SIZE_Y;
	
	sf::View view;
	view.setCenter(sf::Vector2f(m_fWidth / 2.0f, m_fHeight / 2.0f));
	view.setSize(sf::Vector2f((float)m_fWidth, (float)m_fHeight));

	sf::RenderWindow::setSize(sf::Vector2u(m_fWidth, m_fHeight));
	sf::RenderWindow::setView(view);

	m_InputManager = new sfgmk::InputManager(this);
}
#endif

#ifndef SFGMKR_EDITOR
SFMLCanvas::SFMLCanvas()
{
	sf::RenderWindow::create(sf::VideoMode((unsigned int)SFGMKR_DEFAULT_SFML_SIZE_X, (unsigned int)SFGMKR_DEFAULT_SFML_SIZE_Y), "SFGMK Reloaded");

	m_fWidth = SFGMKR_DEFAULT_SFML_SIZE_X;
	m_fHeight = SFGMKR_DEFAULT_SFML_SIZE_Y;

	sf::View view;
	view.setCenter(sf::Vector2f(m_fWidth / 2.0f, m_fHeight / 2.0f));
	view.setSize(sf::Vector2f((float)m_fWidth, (float)m_fHeight));

	sf::RenderWindow::setSize(sf::Vector2u((unsigned int)m_fWidth, (unsigned int)m_fHeight));
	sf::RenderWindow::setView(view);

	m_InputManager = new sfgmk::InputManager(this);
}
#endif

SFMLCanvas::~SFMLCanvas()
{
	delete m_InputManager;
}

#ifdef SFGMKR_EDITOR
void SFMLCanvas::OnIdle(wxIdleEvent& _event)
{
	// On génère un rafraîchissement du contrôle, afin d'assurer un framerate maximum
	Refresh(false);

	_event.RequestMore(true);
}

void SFMLCanvas::OnPaint(wxPaintEvent& _event)
{
	// On prépare le contrôle à être dessiné
	wxPaintDC dc(this);

	sf::Clock clock;
	clock.restart();

	// On laisse la classe dérivée se mettre à jour et dessiner dans le contrôle
	OnUpdate();
}

void SFMLCanvas::OnEraseBackground(wxEraseEvent& _event)
{

}

BEGIN_EVENT_TABLE(SFMLCanvas, wxPanel)
	EVT_IDLE(SFMLCanvas::OnIdle)
	EVT_ERASE_BACKGROUND(SFMLCanvas::OnEraseBackground)
	EVT_PAINT(SFMLCanvas::OnPaint)
END_EVENT_TABLE()
#endif

void SFMLCanvas::OnUpdate()
{
	// On efface la vue
	clear(sf::Color(0, 128, 128));

	// Pre update
	m_InputManager->update();
	sfgmk::TimeManager::GetSingleton()->update();

	// Update gameobjects / components
	sfgmk::vector<GameObject*>& gameobjects = GameObjectManager::GetSingleton()->getGameObjects();

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
		gameobjects[i]->update();

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
		gameobjects[i]->draw(this);

	// On affiche tout ça à l'écran
	display();
}

sfgmk::InputManager* SFMLCanvas::getInputManager()
{
	return m_InputManager;
}

#ifdef SFGMKR_EDITOR
bool SFMLCanvas::isPlaying = false;
#else
bool SFMLCanvas::isPlaying = true;
#endif