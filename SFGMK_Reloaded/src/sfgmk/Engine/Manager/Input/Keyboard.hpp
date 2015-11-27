/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		29/11/2014
	@brief		Fichier d'ent�te de Keyboard

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMK_KEYBOARD_HPP
#define SFGMK_KEYBOARD_HPP


namespace sfgmk
{
	class Keyboard
	{
		friend class InputManager;

	public:
		void updateKeyboard();
		void handleEvent(sf::Event _event);

		char getLastChar();
		int getKeyState(sf::Keyboard::Key _key);

	private:
		Keyboard(InputManager* _manager);
		~Keyboard();

		char m_LastChar;
		int m_KeyStates[sf::Keyboard::KeyCount];

		InputManager* m_Manager;
	};
}


#endif