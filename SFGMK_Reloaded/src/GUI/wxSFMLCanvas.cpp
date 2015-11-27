wxSFMLCanvas::wxSFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style)
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

wxSFMLCanvas::~wxSFMLCanvas()
{
	delete m_InputManager;
}

void wxSFMLCanvas::OnIdle(wxIdleEvent& _event)
{
	// On génère un rafraîchissement du contrôle, afin d'assurer un framerate maximum
	Refresh();
}

void wxSFMLCanvas::OnPaint(wxPaintEvent& _event)
{
	// On prépare le contrôle à être dessiné
	wxPaintDC dc(this);

	// On efface la vue
	clear(sf::Color(0, 128, 128));

	// Pre update
	m_InputManager->update();

	// On laisse la classe dérivée se mettre à jour et dessiner dans le contrôle
	OnUpdate();

	// On affiche tout ça à l'écran
	display();
}

void wxSFMLCanvas::OnEraseBackground(wxEraseEvent& _event)
{

}

void wxSFMLCanvas::OnUpdate()
{
	sfgmk::vector<GameObject*>& gameobjects = GameObjectManager::GetSingleton()->getGameObjects();

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
		gameobjects[i]->update();

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
		gameobjects[i]->draw(this);
}

BEGIN_EVENT_TABLE(wxSFMLCanvas, wxPanel)
EVT_IDLE(wxSFMLCanvas::OnIdle)
EVT_ERASE_BACKGROUND(wxSFMLCanvas::OnEraseBackground)
EVT_PAINT(wxSFMLCanvas::OnPaint)
END_EVENT_TABLE()