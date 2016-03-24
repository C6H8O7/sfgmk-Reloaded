#ifndef SFGMKR_GAMEOBJECT_HPP
#define SFGMKR_GAMEOBJECT_HPP

#include "stdafx.h"

class GameObject
{
public:

	struct sGAMEOBJECT_PHYSICFUNCS
	{
		r_void(*enter)(r_void*);
		r_void(*collision)(r_void*, GameObject*);
		r_void(*exit)(r_void*);
		r_void* object;
	};

	GameObject();
	GameObject(r_bool _createDefault);
	GameObject(GameObject* _Object);
	~GameObject();

	///////////////////////////////////////////////////////////////////////// Variables

	GameObject* ptr = this;

	r_transform transform;
	r_transform* transformPtr = &transform;

	r_transform localTransform;
	r_transform* localTransformPtr = &localTransform;

	gmk::Rigidbody* rigidbodyPtr = 0;

	gmk::vector<gmk::PathfindingAgent*> pathfindingAgents;

	gmk::Debug debug;
	gmk::Debug* debugPtr = &debug;

	gmk::Steering* steeringPtr = 0;

	r_string text;

	r_string name = "GameObject";
	r_string tag;

	ComponentSoundBuffer* soundBufferPtr = 0;

	r_void* treeID = 0;

	///////////////////////////////////////////////////////////////////////// Methods

	r_void update(SFMLCanvas * _canvas);
	r_void draw(SFMLCanvas* _canvas);

	r_void destroy();

	///////////////////////////////////////////////////////////////////////// Components

	r_void addDefaultComponents();

	GameObjectComponent* getComponent(r_string _name);
	gmk::vector<GameObjectComponent*>& getComponents();
	gmk::vector<GameObjectComponent*> getComponents(r_string _name);

	r_void addComponent(GameObjectComponent* _component);
	r_void removeComponent(GameObjectComponent* _component);

#ifdef SFGMKR_EDITOR
	r_void showComponents(r_bool _value);
	r_void updateComponents();

	static r_void AddAsComponent(GameObject* _object, r_string _componentPath);
#endif

	///////////////////////////////////////////////////////////////////////// Physic

	r_void onPhysicEnter();
	r_void onPhysicCollisionEnter(GameObject* _object);
	r_void onPhysicCollision(GameObject* _object);
	r_void onPhysicExit();

	r_vector2f getCenter();

	r_void addPhysicFuncs(sGAMEOBJECT_PHYSICFUNCS* _funcs);
	r_void removePhysicFuncs(sGAMEOBJECT_PHYSICFUNCS* _funcs);

	///////////////////////////////////////////////////////////////////////// Script

	r_void registerScript(ComponentScript* _component);
	r_void unregisterScript(ComponentScript* _component);

	gmk::vector<ComponentScript*>& getScripts();
	gmk::LuaScript getScriptByName(r_string _name);

	///////////////////////////////////////////////////////////////////////// IA

	r_void computePathfinding(r_vector2f _begin, r_vector2f _end, r_bool _smooth, r_float _caseSize);

	///////////////////////////////////////////////////////////////////////// Parent System

	r_void setParent(GameObject* _gameObject);
	GameObject*& getParent();
	gmk::vector<GameObject*>& getChildren();

	///////////////////////////////////////////////////////////////////////// Save / Load

	r_void OnXMLSave(tinyxml2::XMLElement* _element);
	r_void OnXMLLoad(tinyxml2::XMLElement* _element);

private:

	gmk::vector<sGAMEOBJECT_PHYSICFUNCS*> m_PhysicFuncs;

	gmk::vector<GameObjectComponent*> m_Components;

	gmk::vector<ComponentScript*> m_Scripts;

	GameObject* m_parent = 0;
	gmk::vector<GameObject*> m_children;

	r_bool m_pendingDeletion = false;
};

#endif