/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		10/12/2014
	@brief		Singleton regroupant l'ensemble des accés clavier, souris et joystick

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMK_INPUT_MANAGER_HPP
#define SFGMK_INPUT_MANAGER_HPP

#define KEY_UP							sfgmk::eKeyStates::eKEY_UP
#define KEY_PRESSED						sfgmk::eKeyStates::eKEY_PRESSED
#define KEY_DOWN						sfgmk::eKeyStates::eKEY_DOWN
#define KEY_RELEASED					sfgmk::eKeyStates::eKEY_RELEASED

namespace sfgmk
{
	enum eKeyStates
	{
		eKEY_UP = 0,
		eKEY_PRESSED = 1 << 0,
		eKEY_DOWN = eKEY_PRESSED | 1 << 1,
		eKEY_RELEASED = 1 << 2,
	};

	enum eMouseWheelStates
	{
		eWHEEL_BOT = -1,
		eWHEEL_CENTER = 0,
		eWHEEL_TOP = 1
	};

	class InputManager
	{
		public:
			InputManager(sf::RenderWindow* _window);
			~InputManager();

			void update();
			void handleEvents();

			Keyboard& getKeyboard();
			Mouse& getMouse();

			sf::RenderWindow* getRenderWindow();

		private:

			sf::Event m_Event;

			Keyboard*	m_Keyboard;
			Mouse*		m_Mouse;

			sf::RenderWindow* m_Window;
	};
}


#endif