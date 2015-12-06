#ifdef SFGMKR_EDITOR

SFMLEditorCanvas::SFMLEditorCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style)
	: SFMLCanvas(Parent, Id, Position, Size, Style)
{
	m_TextureGrid.loadFromFile("../data/editor/grid.png");

	m_SpriteGrid.setTexture(m_TextureGrid);

	m_Zoom = 1.0f;
}

SFMLEditorCanvas::~SFMLEditorCanvas()
{

}

bool SFMLEditorCanvas::isEditor()
{
	return true;
}

void SFMLEditorCanvas::OnPaint(wxPaintEvent& _event)
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
}

void SFMLEditorCanvas::OnEditionBasicDragPos()
{
	MyGUI* gui = MyGUI::GetGUI();

	GameObject *gameobject = gui->selectedGameObject;

	if (gameobject)
	{
		gmk::Mouse& mouse = m_InputManager->getMouse();

		int state = mouse.getButtonState(sf::Mouse::Left);

		if (state == KEY_PRESSED)
		{
			m_BasicDragPosMouseBegin = mouse.getWorldPosition();
			m_BasicDragPosTransformBegin = gameobject->transform.position;
		}
		else if (state == KEY_DOWN)
		{
			sf::Vector2f diff = mouse.getWorldPosition() - m_BasicDragPosMouseBegin;
			gameobject->transform.position = m_BasicDragPosTransformBegin + diff;

			gui->Update_PropertyGrid();
		}
	}
}

void SFMLEditorCanvas::OnEditionBasicDragCamera()
{
	sf::View view = getView();

	gmk::Mouse& mouse = m_InputManager->getMouse();

	int state = mouse.getButtonState(sf::Mouse::Middle);

	if (state == KEY_PRESSED)
	{
		m_BasicDragPosMouseBegin = sf::Vector2f(mouse.getWindowPosition());
		m_BasicDragPosCameraBegin = view.getCenter();
	}
	else if (state == KEY_DOWN)
	{
		sf::Vector2f diff = sf::Vector2f(mouse.getWindowPosition()) - m_BasicDragPosMouseBegin;

		view.setCenter(m_BasicDragPosCameraBegin - diff);
		setView(view);
	}
}

void SFMLEditorCanvas::OnEditionBasicZoomCamera()
{
	sf::View view = getView();

	gmk::Mouse& mouse = m_InputManager->getMouse();

	int tick = mouse.getWheelState();

	if (tick)
	{
		m_Zoom -= tick * 0.1f;

		if (m_Zoom <= 0.0f)
			m_Zoom = 0.1f;

		view.setSize(m_DefaultWidth * m_Zoom, m_DefaultHeight * m_Zoom);
		setView(view);
	}
}

void SFMLEditorCanvas::OnEditionDrawGrid()
{
	for (int x = -1; x < 6; x++)
	{
		for (int y = -1; y < 4; y++)
		{
			m_SpriteGrid.setPosition(x * 256.0f, y * 256.0f);
			draw(m_SpriteGrid);
		}
	}
}

void SFMLEditorCanvas::OnUpdate()
{
	OnEditionBasicDragPos();
	OnEditionBasicDragCamera();
	OnEditionBasicZoomCamera();

	OnEditionDrawGrid();

	sfgmk::vector<GameObject*>& gameobjects = SFMLCanvas::project->getCurrentScene()->getGameObjects();

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
		gameobjects[i]->draw(this);
}

#endif