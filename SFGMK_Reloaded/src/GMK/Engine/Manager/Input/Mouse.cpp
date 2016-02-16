#include "stdafx.h"

namespace gmk
{
	Mouse::Mouse(InputManager* _manager) : m_iWheelState(0), m_Manager(_manager)
	{
		for( r_int32 i(0); i < sf::Mouse::ButtonCount; i++ )
			m_KeyStates[i] = KEY_UP;
	}

	Mouse::~Mouse()
	{

	}

	r_void Mouse::updateMouse()
	{
		for( r_int32 i(0); i < sf::Mouse::ButtonCount; i++ )
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

	r_void Mouse::handleEvent(sf::Event _Event)
	{
		r_int32 key;

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
				break;

			case sf::Event::TouchBegan:
				m_KeyStates[sf::Mouse::Left] = eKeyStates::eKEY_PRESSED;
				break;

			case sf::Event::TouchEnded:
				m_KeyStates[sf::Mouse::Left] = eKeyStates::eKEY_RELEASED;
				break;

			default:
				break;
		}
	}

	r_vector2i Mouse::getWindowPosition()
	{
#ifndef SFGMKR_ANDROID
		return sf::Mouse::getPosition(m_Manager->getCanvas()->window);
#else
		return sf::Touch::getPosition(0, m_Manager->getCanvas()->window);
#endif
	}

	r_vector2f Mouse::getWorldPosition()
	{
		sf::View view = m_Manager->getCanvas()->getView();
		sf::Vector2u size = m_Manager->getCanvas()->window.getSize();

		r_vector2f viewPosition(view.getCenter());
		r_vector2f viewSize(view.getSize());

		r_vector2f ratio = r_vector2f(viewSize.x / size.x, viewSize.y / size.y);

		r_vector2f position = r_vector2f(windowPosition);

		position.x *= ratio.x;
		position.y *= ratio.y;

		position = position + viewPosition - viewSize * 0.5f;

		return position;
	}

	r_int32 Mouse::getButtonState(sf::Mouse::Button _Button)
	{
		return m_KeyStates[_Button];
	}

	r_int32 Mouse::getWheelState()
	{
		return m_iWheelState;
	}
}