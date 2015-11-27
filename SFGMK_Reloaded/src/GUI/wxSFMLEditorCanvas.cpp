wxSFMLEditorCanvas::wxSFMLEditorCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style)
	: wxSFMLCanvas(Parent, Id, Position, Size, Style)
{

}

wxSFMLEditorCanvas::~wxSFMLEditorCanvas()
{

}

void wxSFMLEditorCanvas::OnPaint(wxPaintEvent& _event)
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

void wxSFMLEditorCanvas::OnEditionBasicDragPos()
{
	MyGUI* gui = MyGUI::GetGUI();

	GameObject *gameobject = gui->selectedGameObject;

	if (gameobject)
	{
		sfgmk::Mouse& mouse = m_InputManager->getMouse();

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

void wxSFMLEditorCanvas::OnUpdate()
{
	OnEditionBasicDragPos();

	sfgmk::vector<GameObject*>& gameobjects = GameObjectManager::GetSingleton()->getGameObjects();

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
		gameobjects[i]->update();

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
		gameobjects[i]->draw(this);
}