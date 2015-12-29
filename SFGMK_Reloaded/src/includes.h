#ifndef INCLUDES_H
#define INCLUDES_H

#define SFGMKR_MYGUI_DEBUG true
#define SFGMKR_ASSETSMANAGER_DEBUG true

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
	#include <SFML\System.hpp>
	#include <SFML\Graphics.hpp>
	#include <SFML\Window.hpp>

// Windows

	#include <Windows.h>

// LUA

	#include <lua.hpp>
	#include "Utils\extern\luabridge\LuaBridge.h"

// tinyxml2

	#include "Utils\extern\tinyxml2\tinyxml2.h"

//Clipper

	#include "Utils\extern\clipper\cpp\clipper.hpp"

// poly2tri

	#include "Utils\extern\poly2tri\geometry.h"
	#include "Utils\extern\poly2tri\parse.h"

// C++

	#include <iostream>

// OMP

	#include <omp.h>

// sfgmk reloaded

	#include "Utils\vector.hpp"

	#include "GMK\Math\Math.hpp"
	#include "GMK\Math\Curb\Curb.hpp"
	#include "GMK\Math\Curb\Bezier.hpp"
	#include "GMK\Math\Curb\CatmullRom.hpp"
	#include "GMK\Math\Matrix\Matrix22.hpp"
	#include "GMK\Math\Matrix\MatrixRotation22.hpp"
	#include "GMK\Math\Curb\CoordinateSystem\GraphCurb.hpp"

	#include "GMK\Physic\Collider.hpp"
	#include "GMK\Physic\ObbCollider.hpp"

	#include "GMK\Engine\Manager\Time\TimeManager.hpp"

	#include "GMK\Engine\Manager\Input\Mouse.hpp"
	#include "GMK\Engine\Manager\Input\Keyboard.hpp"
	#include "GMK\Engine\Manager\Input\InputManager.hpp"

	#include "GMK\Engine\Manager\Assets\AssetsManager.hpp"

	#include "GMK\Map\TiledMap.hpp"

	#include "GMK\Particle\Particle.hpp"
	#include "GMK\Particle\ParticleSystem.hpp"

	#include "GMK\Reloaded\GameObject\Transform.hpp"

	#include "GMK\Reloaded\GameObject\Component\GameObjectComponent.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentGameObject.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentTransform.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentSprite.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentScript.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentCamera.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentParticleSystem.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentTiledMap.hpp"

	#include "GMK\Reloaded\GameObject\GameObject.hpp"

	#include "GMK\Reloaded\Scene.hpp"
	#include "GMK\Reloaded\Project.hpp"

	#include "GUI\SFMLCanvas.hpp"

#ifdef SFGMKR_EDITOR
	#include "GUI\SFMLEditorCanvas.hpp"
	#include "GUI\wxMyGenericDirCtrl.hpp"
	#include "GUI\wxMyTextDropTarget.hpp"

	#include "GUI\GUI.h"
	#include "GUI\MyGUI.hpp"
#endif

#endif