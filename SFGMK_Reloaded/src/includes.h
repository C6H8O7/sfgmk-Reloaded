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

	#include "GUI\wxWorkspaceView\wxWorkspaceView.h"
	#include "GUI\wxWorkspaceView\BasicWorkspace.h"
	#include "GUI\wxWorkspaceView\ThijzWorkspace.h"
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
	#include <unordered_map>

#ifndef SFGMKR_ANDROID
#ifndef SFGMKR_EDITOR

	#define _WINSOCK_DEPRECATED_NO_WARNINGS

	#include <WinSock2.h>
	#include <WS2tcpip.h>

	#include <Windows.h>
#endif

	#pragma comment(lib, "Ws2_32.lib")

#endif

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
	#include "GMK\Tool\CircularBuffer.hpp"

	#include "GMK\Tool\MyMutex.h"
	#include "GMK\Tool\MySemaphore.h"
	#include "GMK\Tool\MyCircularBuffer.h"

	#include "GMK\Net\Address.hpp"
	#include "GMK\Net\Packet.hpp"
	#include "GMK\Net\Socket.hpp"
	#include "GMK\Net\UdpSocket.hpp"
	#include "GMK\Net\NetActor.hpp"
	#include "GMK\Net\NetClient.hpp"
	#include "GMK\Net\NetHost.hpp"

	#include "GMK\Math\Math.hpp"
	#include "GMK\Math\Curb\Curb.hpp"
	#include "GMK\Math\Curb\Bezier.hpp"
	#include "GMK\Math\Curb\CatmullRom.hpp"
	#include "GMK\Math\Matrix\Matrix22.hpp"
	#include "GMK\Math\Matrix\MatrixRotation22.hpp"
	#include "GMK\Math\Curb\CoordinateSystem\GraphCurb.hpp"

	#include "GMK\NavMesh\Polygon.hpp"

	#include "GMK\Render\SpriteAnimation.hpp"
	#include "GMK\Render\Sprite.hpp"

	#include "GMK\IA\NeuronalNetwork\NeuronalNetwork.hpp"
	#include "GMK\IA\NeuronalNetwork\NeuronNetwork.hpp"

	#include "GMK\IA\PathfindingMap\PathfindingMap.hpp"
	#include "GMK\IA\Pathfinding\Pathfinding.hpp"
	#include "GMK\IA\Pathfinding\PathfindingAgent.hpp"
	#include "GMK\IA\PathfindingMap\MapGenerator\Room.hpp"
	#include "GMK\IA\PathfindingMap\MapGenerator\MapGenerator.hpp"

	#include "GMK\IA\Steering\Behavior\SteeringBehavior.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringSeek.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringFlee.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringPursuit.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringEvasion.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringArrival.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringObstacleAvoidance.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringWander.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringLeadFollowing.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringSeparation.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringCohesion.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringAlignment.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringUnalignedCollisionAvoidance.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringPathFollowing.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringSwarming.hpp"
	#include "GMK\IA\Steering\Behavior\SteeringFormationAgent.hpp"

	#include "GMK\IA\Steering\SteeringFormation.hpp"
	#include "GMK\IA\Steering\Steering.hpp"

	#include "GMK\IA\BehaviorTree\Behavior.hpp"
	#include "GMK\IA\BehaviorTree\Leaves\BehaviorTreeLeaf.hpp"
	#include "GMK\IA\BehaviorTree\Composites\BehaviorTreeComposite.hpp"
	#include "GMK\IA\BehaviorTree\Composites\BehaviorTreeSequence.hpp"
	#include "GMK\IA\BehaviorTree\Decorators\BehaviorTreeDecorator.hpp"
	#include "GMK\IA\BehaviorTree\Decorators\BehaviorTreeRepeater.hpp"
	#include "GMK\IA\BehaviorTree\BehaviorTree.hpp"

	#include "GMK\IA\GOAP\PlannerAction.hpp"
	#include "GMK\IA\GOAP\Planner.hpp"

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

	#include "GMK\Engine\Manager\IA\SteeringManager.hpp"

	#include "GMK\Engine\Manager\Net\PacketHandling.hpp"
	#include "GMK\Engine\Manager\Net\NetworkManager.hpp"

	#include "GMK\Engine\Manager\Render\RenderManager.hpp"

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

	#include "GMK\Reloaded\GameObject\Component\Render\ComponentSprite.hpp"
	#include "GMK\Reloaded\GameObject\Component\Render\ComponentCamera.hpp"
	#include "GMK\Reloaded\GameObject\Component\Render\ComponentParticleSystem.hpp"
	#include "GMK\Reloaded\GameObject\Component\Render\ComponentTiledMap.hpp"
	#include "GMK\Reloaded\GameObject\Component\Render\ComponentShader.hpp"
	#include "GMK\Reloaded\GameObject\Component\Render\ComponentText.hpp"
	#include "GMK\Reloaded\GameObject\Component\Render\ComponentPostShader.hpp"

	#include "GMK\Reloaded\GameObject\Component\ComponentScript.hpp"

	#include "GMK\Reloaded\GameObject\Component\ComponentPolygon.hpp"
	#include "GMK\Reloaded\GameObject\Component\Render\ComponentShapeContainer.hpp"

	#include "GMK\Reloaded\GameObject\Component\IA\NeuronalNetwork\ComponentNeuronalNetwork.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Pathfinding\ComponentPathfindingMap.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Pathfinding\ComponentPathfindingAgent.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Pathfinding\Neural\ComponentNPathfindingMap.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Pathfinding\Neural\ComponentNPathfindingAgent.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteering.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringSeek.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringFlee.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringPursuit.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringEvasion.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringArrival.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringObstacleAvoidance.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringWander.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringLeadFollowing.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringSeparation.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringCohesion.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringAlignment.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringUnalignedCollisionAvoidance.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringPathFollowing.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringSwarming.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringFormationAgent.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringFormation.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\Steering\ComponentSteeringAgent.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\BehaviorTree\ComponentBehaviorTree.hpp"
	#include "GMK\Reloaded\GameObject\Component\IA\GOAP\ComponentPlanner.hpp"

	#include "GMK\Reloaded\GameObject\Component\Net\ComponentLANReplication.hpp"

	#include "GMK\Reloaded\GameObject\Component\Physic\ComponentCollider.hpp"
	#include "GMK\Reloaded\GameObject\Component\Physic\ComponentRigidbody.hpp"

	#include "GMK\Reloaded\GameObject\Component\Debug\ComponentSelector.hpp"

	#include "GMK\Reloaded\GameObject\Component\Audio\ComponentListener.hpp"
	#include "GMK\Reloaded\GameObject\Component\Audio\ComponentSoundBuffer.hpp"

	#include "GMK\Reloaded\GameObject\GameObject.hpp"

	#include "GMK\Engine\Manager\Factory\Prefab.hpp"
	#include "GMK\Engine\Manager\Factory\Factory.hpp"

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

	#include "GUI\ScriptEditor.hpp"
	#include "GUI\MyGUI.hpp"
#endif

#endif