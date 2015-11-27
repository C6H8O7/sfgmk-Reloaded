namespace sfgmk
{
	InputManager::InputManager(sf::RenderWindow* _window) : m_Window(_window)
	{
		m_Mouse = new Mouse(this);
		m_Keyboard = new Keyboard(this);
	}

	InputManager::~InputManager()
	{
		delete m_Mouse;
		delete m_Keyboard;
	}

	void InputManager::update()
	{
		m_Keyboard->updateKeyboard();

		m_Mouse->updateMouse();

		handleEvents();
	}

	void InputManager::handleEvents()
	{
		while(m_Window->pollEvent(m_Event))
		{
			if( m_Event.type == sf::Event::Closed )
				m_Window->close();

			m_Keyboard->handleEvent(m_Event);

			m_Mouse->handleEvent(m_Event);
		}
	}

	Keyboard& InputManager::getKeyboard()
	{
		return *m_Keyboard;
	}

	Mouse& InputManager::getMouse()
	{
		return *m_Mouse;
	}

	sf::RenderWindow* InputManager::getRenderWindow()
	{
		return m_Window;
	}
}