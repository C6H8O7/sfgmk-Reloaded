/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		10/12/2014
	@brief		Fichier d'entête de Mouse

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMK_MOUSE_HPP
#define SFGMK_MOUSE_HPP

#include "stdafx.h"

namespace gmk
{
	class InputManager;
	
	class Mouse
	{
		friend class InputManager;

	public:
		r_void updateMouse();
		r_void handleEvent(sf::Event _Event);

		r_vector2i windowPosition;
		r_vector2f worldPosition;
		r_vector2i unscaledWindowPosition;

		r_vector2i getWindowPosition();
		r_vector2f getWorldPosition();
		r_vector2i getUnscaledWindowPosition();

		r_int32 getButtonState(sf::Mouse::Button _Button);
		//0 = pas de roulement, 1 = roulement haut, -1 roulemant bas
		r_int32 getWheelState();

		r_int32 m_KeyStates[sf::Mouse::ButtonCount];
		r_int32 m_iWheelState;

	private:
		Mouse(InputManager* _manager);
		~Mouse();

		InputManager* m_Manager;
	};
}


#endif