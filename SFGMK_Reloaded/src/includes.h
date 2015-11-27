#ifndef INCLUDES_H
#define INCLUDES_H

// wxWidgets

	#include <wx\wx.h>

	#include <wx\propgrid\propgrid.h>
	#include <wx\propgrid\advprops.h>

// SFML

	#include <SFML\Config.hpp>
	#include <SFML\Graphics.hpp>
	#include <SFML\System.hpp>
	#include <SFML\Window.hpp>

// LUA

	#include <lua.hpp>

// Perso

	#include "Utils\extern\tinyxml2\tinyxml2.h"
	#include "Utils\vector.hpp"

	#include "GameObject\Transform.hpp"

	#include "GameObject\Component\GameObjectComponent.hpp"
	#include "GameObject\Component\ComponentSprite.hpp"

	#include "GameObject\GameObject.hpp"
	#include "GameObject\GameObjectManager.hpp"

	#include "GUI\wxSFMLCanvas.hpp"
	#include "GUI\GUI.h"
	#include "GUI\MyGUI.hpp"

#endif