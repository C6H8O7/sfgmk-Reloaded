#ifdef SFGMKR_EDITOR
SFMLCanvas::SFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style)
	: wxPanel(Parent, Id, Position, Size, Style)
{
	sf::RenderWindow::create(GetHandle());

	m_fWidth = SFGMKR_DEFAULT_SFML_SIZE_X;
	m_fHeight = SFGMKR_DEFAULT_SFML_SIZE_Y;
	
	sf::View view;
	view.setCenter(sf::Vector2f(m_fWidth / 2.0f, m_fHeight / 2.0f));
	view.setSize(sf::Vector2f((float)m_fWidth, (float)m_fHeight));

	sf::RenderWindow::setSize(sf::Vector2u(m_fWidth, m_fHeight));
	sf::RenderWindow::setView(view);

	m_InputManager = new gmk::InputManager(this);
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

	m_InputManager = new gmk::InputManager(this);
}
#endif

SFMLCanvas::~SFMLCanvas()
{
	delete m_InputManager;
}

#ifdef SFGMKR_EDITOR
void SFMLCanvas::OnIdle(wxIdleEvent& _event)
{
	// On g�n�re un rafra�chissement du contr�le, afin d'assurer un framerate maximum
	Refresh(false);

	_event.RequestMore(true);
}

void SFMLCanvas::OnPaint(wxPaintEvent& _event)
{
	// On pr�pare le contr�le � �tre dessin�
	wxPaintDC dc(this);

	// On laisse la classe d�riv�e se mettre � jour et dessiner dans le contr�le
	OnUpdate();

#ifdef SFGMKR_EDITOR
	static float timer = 0;
	static float* timeDeltaPtr = &sfgmk::TimeManager::GetSingleton()->deltaTime;

	timer += *timeDeltaPtr;

	if (timer >= 0.05f)
	{
		timer = 0.0f;

		MyGUI* gui = MyGUI::GetGUI();

		gui->Update_PropertyGrid();

		char status[50];
		sprintf_s(status, "Updated in: %.2f ms (%d FPS)", *timeDeltaPtr * 1000.0f, (int)(1.0f / *timeDeltaPtr));
		gui->GUI_StatusBar->SetStatusText(status);
	}
#endif
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
	sfgmk::vector<GameObject*>& gameobjects = SFMLCanvas::project->getCurrentScene()->getGameObjects();

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
		gameobjects[i]->update(this);

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
		gameobjects[i]->draw(this);

	// On affiche tout �a � l'�cran
	display();
}

gmk::InputManager* SFMLCanvas::getInputManager()
{
	return m_InputManager;
}

bool SFMLCanvas::isEditor()
{
	return false;
}

#ifdef SFGMKR_EDITOR
	bool SFMLCanvas::isPlaying = false;
#else
	bool SFMLCanvas::isPlaying = true;
#endif
	
SFMLCanvas* SFMLCanvas::gameCanvas = 0;
SFMLCanvas* SFMLCanvas::editorCanvas = 0;
Project* SFMLCanvas::project = 0;