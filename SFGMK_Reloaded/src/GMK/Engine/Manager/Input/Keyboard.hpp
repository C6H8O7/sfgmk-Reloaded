/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		29/11/2014
	@brief		Fichier d'entête de Keyboard

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMK_KEYBOARD_HPP
#define SFGMK_KEYBOARD_HPP

#include "stdafx.h"

namespace gmk
{
	class Keyboard
	{
		friend class InputManager;

	public:
		r_void updateKeyboard();
		r_void handleEvent(sf::Event _event);

		r_int8 getLastChar();
		r_int32 getKeyState(sf::Keyboard::Key _key);

	private:
		Keyboard(InputManager* _manager);
		~Keyboard();

		r_int8 m_LastChar;
		r_int32 m_KeyStates[sf::Keyboard::KeyCount];

		InputManager* m_Manager;
	};
}


#endif