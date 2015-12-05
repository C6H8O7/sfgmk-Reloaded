namespace gmk
{
	Mouse::Mouse(InputManager* _manager) : m_iWheelState(0), m_Manager(_manager)
	{
		for( int i(0); i < sf::Mouse::ButtonCount; i++ )
			m_KeyStates[i] = KEY_UP;
	}

	Mouse::~Mouse()
	{

	}

	void Mouse::updateMouse()
	{
		for( int i(0); i < sf::Mouse::ButtonCount; i++ )
		{
			if( m_KeyStates[i] == KEY_PRESSED )
				m_KeyStates[i] = KEY_DOWN;
			else if( m_KeyStates[i] == KEY_RELEASED )
				m_KeyStates[i] = KEY_UP;
		}

		m_iWheelState = 0;

		windowPosition = getWindowPosition();
		worldPosition = getWorldPosition();
	}

	void Mouse::handleEvent(sf::Event _Event)
	{
		int key;

		switch( _Event.type )
		{
			case sf::Event::MouseButtonPressed:
				key = _Event.key.code;
				if( m_KeyStates[key] == eKeyStates::eKEY_UP )
					m_KeyStates[key] = eKeyStates::eKEY_PRESSED;
				break;

			case sf::Event::MouseButtonReleased:
				key = _Event.key.code;
				m_KeyStates[key] = eKeyStates::eKEY_RELEASED;
				break;

			case sf::Event::MouseWheelMoved:
				m_iWheelState = _Event.key.code;

			default:
				break;
		}
	}

	sf::Vector2i Mouse::getWindowPosition()
	{
		return sf::Mouse::getPosition(*m_Manager->getRenderWindow());
	}

	sf::Vector2f Mouse::getWorldPosition()
	{
		sf::View view = m_Manager->getRenderWindow()->getView();
		sf::Vector2u size = m_Manager->getRenderWindow()->getSize();

		sf::Vector2f viewPosition(view.getCenter());
		sf::Vector2f viewSize(view.getSize());

		sf::Vector2f ratio = sf::Vector2f(viewSize.x / size.x, viewSize.y / size.y);

		sf::Vector2f position = sf::Vector2f(getWindowPosition());

		position.x *= ratio.x;
		position.y *= ratio.y;

		position = position + viewPosition - viewSize * 0.5f;

		return position;
	}

	int Mouse::getButtonState(sf::Mouse::Button _Button)
	{
		return m_KeyStates[_Button];
	}

	int Mouse::getWheelState()
	{
		return m_iWheelState;
	}
}