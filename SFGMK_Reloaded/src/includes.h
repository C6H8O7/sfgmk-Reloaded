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
	#include <SFML\System.hpp>
	#include <SFML\Graphics.hpp>
	#include <SFML\Audio.hpp>
	#include <SFML\Window.hpp>

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

#ifndef SFGMKR_ANDROID
	#include <thread>
#endif

// sfgmk reloaded

	#include "defs.h"

	#include "GMK\Tool\Functions.hpp"

	#include "GMK\Tool\IO.hpp"
	#include "GMK\Tool\vector.hpp"
	#include "GMK\Tool\SingletonTemplate.hpp"
	#include "GMK\Tool\FoncterTemplate.hpp"
	#include "GMK\Tool\ThreadTemplate.hpp"

	#include "GMK\Math\Math.hpp"
	#include "GMK\Math\Curb\Curb.hpp"
	#include "GMK\Math\Curb\Bezier.hpp"
	#include "GMK\Math\Curb\CatmullRom.hpp"
	#include "GMK\Math\Matrix\Matrix22.hpp"
	#include "GMK\Math\Matrix\MatrixRotation22.hpp"
	#include "GMK\Math\Curb\CoordinateSystem\GraphCurb.hpp"

	#include "GMK\NavMesh\Polygon.hpp"

	#include "GMK\IA\PathfindingMap\PathfindingMap.hpp"
	#include "GMK\IA\Pathfinding\Pathfinding.hpp"
	#include "GMK\IA\Pathfinding\PathfindingAgent.hpp"
	#include "GMK\IA\PathfindingMap\MapGenerator\Room.hpp"
	#include "GMK\IA\PathfindingMap\MapGenerator\MapGenerator.hpp"

	#include "GMK\Physic\Collider.hpp"
	#include "GMK\Physic\ObbCollider.hpp"
	#include "GMK\Physic\SphereCollider.hpp"

	#include "GMK\Physic\Rigidbody.hpp"

	#include "GMK\Engine\Manager\Time\TimeManager.hpp"

	#include "GMK\Engine\Manager\Input\Mouse.hpp"
	#include "GMK\Engine\Manager\Input\Keyboard.hpp"
	#include "GMK\Engine\Manager\Input\InputManager.hpp"

	#include "GMK\Engine\Manager\Assets\AssetsManager.hpp"

	#include "GMK\Engine\Manager\Physic\PhysicManager.hpp"

	#include "GMK\Map\TiledMap.hpp"

	#include "GMK\Particle\Particle.hpp"
	#include "GMK\Particle\ParticleSystem.hpp"

	#include "GMK\Debug\Debug.hpp"
	#include "GMK\Debug\Selector.hpp"

	#include "GMK\Reloaded\GameObject\Transform.hpp"

	#include "GMK\LUA\LUA.hpp"

	#include "GMK\Reloaded\GameObject\Component\GameObjectComponent.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentGameObject.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentTransform.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentSprite.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentScript.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentCamera.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentParticleSystem.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentTiledMap.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentPolygon.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentPathfindingMap.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentPathfindingAgent.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentCollider.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentSelector.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentShader.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentRigidbody.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentText.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentListener.hpp"
	#include "GMK\Reloaded\GameObject\Component\ComponentSoundBuffer.hpp"

	#include "GMK\Reloaded\GameObject\GameObject.hpp"

	#include "GMK\Reloaded\ComponentsBank.hpp"

	#include "GMK\Reloaded\Scene.hpp"
	#include "GMK\Reloaded\Project.hpp"

	#include "GUI\SFMLCanvas.hpp"

#ifdef SFGMKR_EDITOR
	#include "GUI\SFMLEditorCanvas.hpp"

	#include "GUI\wxButtonProperty.hpp"
	#include "GUI\wxMyGenericDirCtrl.hpp"
	#include "GUI\wxMyTextDropTarget.hpp"

	#include "GUI\GUI.h"
	#include "GUI\MyGUI.hpp"
#endif

#endif