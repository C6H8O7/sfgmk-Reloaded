#include "stdafx.h"

namespace gmk
{
	InputManager::InputManager(SFMLCanvas* _canvas) : m_Canvas(_canvas)
	{
		m_Mouse = new Mouse(this);
		m_Keyboard = new Keyboard(this);
	}

	InputManager::~InputManager()
	{
		delete m_Mouse;
		delete m_Keyboard;
	}

	r_void InputManager::update()
	{
		m_Keyboard->updateKeyboard();

		m_Mouse->updateMouse();

		handleEvents();
	}

	r_void InputManager::handleEvents()
	{
		while(m_Canvas->window.pollEvent(m_Event))
		{
			if( m_Event.type == sf::Event::Closed )
				m_Canvas->window.close();

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

	SFMLCanvas* InputManager::getCanvas()
	{
		return m_Canvas;
	}
}