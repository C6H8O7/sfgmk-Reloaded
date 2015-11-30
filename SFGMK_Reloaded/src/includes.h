#ifndef INCLUDES_H
#define INCLUDES_H

// wxWidgets

#ifdef SFGMKR_EDITOR
	#include <wx\wx.h>

	#include <wx\propgrid\propgrid.h>
	#include <wx\propgrid\advprops.h>

	#include <wx\filefn.h>
	#include <wx\dirctrl.h>
	#include <wx\filename.h>

	#include <wx\dnd.h>
#endif

// SFML

	#include <SFML\Config.hpp>
	#include <SFML\Graphics.hpp>
	#include <SFML\System.hpp>
	#include <SFML\Window.hpp>

// Windows

	#include <Windows.h>

// LUA

	#include <lua.hpp>
	#include "Utils\extern\luabridge\LuaBridge.h"

// tinyxml2

	#include "Utils\extern\tinyxml2\tinyxml2.h"

// sfgmk

	#include "sfgmk\Engine\Manager\Time\TimeManager.hpp"

	#include "sfgmk\Engine\Manager\Input\Mouse.hpp"
	#include "sfgmk\Engine\Manager\Input\Keyboard.hpp"
	#include "sfgmk\Engine\Manager\Input\InputManager.hpp"

// sfgmk reloaded

	#include "Utils\vector.hpp"

	#include "GameObject\Transform.hpp"

	#include "GameObject\Component\GameObjectComponent.hpp"
	#include "GameObject\Component\ComponentSprite.hpp"
	#include "GameObject\Component\ComponentScript.hpp"
	#include "GameObject\Component\ComponentCamera.hpp"

	#include "GameObject\GameObject.hpp"
	#include "GameObject\GameObjectManager.hpp"

	#include "Scene\Scene.hpp"

	#include "GUI\SFMLCanvas.hpp"

#ifdef SFGMKR_EDITOR
	#include "GUI\SFMLEditorCanvas.hpp"
	#include "GUI\wxMyGenericDirCtrl.hpp"
	#include "GUI\wxMyTextDropTarget.hpp"

#undef wxMouseEventHandler
#define wxMouseEvent wxTreeEvent
#define wxMouseEventHandler wxTreeEventHandler
#define wxEVT_RIGHT_DOWN wxEVT_TREE_ITEM_MENU
#define PopupMenu(A,B) PopupMenu(A)
#define GUI_HierarchyTreeOnContextMenu virtual GUI_HierarchyTreeOnContextMenu
#define GUI_AssetsDirCtrlOnContextMenu virtual GUI_AssetsDirCtrlOnContextMenu

	#include "GUI\GUI.h"
	#include "GUI\MyGUI.hpp"
#endif
#endif