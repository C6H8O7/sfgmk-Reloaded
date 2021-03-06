#include "stdafx.h"

ComponentsBank::ComponentsBank()
{

}

ComponentsBank::~ComponentsBank()
{
	m_Components.deleteAndClear();
}

ComponentsBank* ComponentsBank::GetSingleton()
{
	static ComponentsBank bank;

	return &bank;
}

r_void ComponentsBank::unregisterComponent(r_string _name)
{
	for (r_int32 i = (r_int32)m_Components.size(); i >= 0; i++)
		if (m_Components[i]->name == _name)
			m_Components.removeElementByIndex(i);
}

GameObjectComponent* ComponentsBank::createComponent(r_string _name, GameObject* _parent)
{
	for (r_uint32 i = 0; i < m_Components.size(); i++)
	{
		sCOMPONENT* component = m_Components[i];

		if (component->name == _name)
			return component->creation.component_ctor(_parent);
	}

	return 0;
}

r_void ComponentsBank::registerAllComponents()
{
	registerComponent<ComponentCamera>("Camera");
	registerComponent<ComponentCollider>("Collider");
	registerComponent<ComponentGameObject>("GameObject");
	registerComponent<ComponentParticleSystem>("ParticleSystem");
	registerComponent<ComponentPathfindingAgent>("PathfindingAgent");
	registerComponent<ComponentPathfindingMap>("PathfindingMap");
	registerComponent<ComponentNPathfindingMap>("NPathfindingMap");
	registerComponent<ComponentNPathfindingAgent>("NPathfindingAgent");
	registerComponent<ComponentPolygon>("Polygon");
	registerComponent<ComponentShapeContainer>("ShapeContainer");
	registerComponent<ComponentRigidbody>("Rigidbody");
	registerComponent<ComponentScript>("Script");
	registerComponent<ComponentSelector>("Selector");
	registerComponent<ComponentSprite>("Sprite");

	registerComponent<ComponentPostShader>("PostShader");

	registerComponent<ComponentNeuronalNetwork>("NeuronalNetwork");
	registerComponent<ComponentSteeringSeek>("SteeringSeek");
	registerComponent<ComponentSteeringFlee>("SteeringFlee");
	registerComponent<ComponentSteeringPursuit>("SteeringPursuit");
	registerComponent<ComponentSteeringEvasion>("SteeringEvasion");
	registerComponent<ComponentSteeringArrival>("SteeringArrival");
	registerComponent<ComponentSteeringObstacleAvoidance>("SteeringObstacleAvoidance");
	registerComponent<ComponentSteeringWander>("SteeringWander");
	registerComponent<ComponentSteeringLeadFollowing>("SteeringLeadFollowing");
	registerComponent<ComponentSteeringSeparation>("SteeringSeparation");
	registerComponent<ComponentSteeringCohesion>("SteeringCohesion");
	registerComponent<ComponentSteeringAlignment>("SteeringAlignment");
	registerComponent<ComponentSteeringUnalignedCollisionAvoidance>("SteeringUnalignedCollisionAvoidance");
	registerComponent<ComponentSteeringPathFollowing>("SteeringPathFollowing");
	registerComponent<ComponentSteeringSwarming>("SteeringSwarming");
	registerComponent<ComponentSteeringFormationAgent>("SteeringFormationAgent");
	registerComponent<ComponentSteeringFormation>("SteeringFormation");
	registerComponent<ComponentSteeringAgent>("SteeringAgent");

	registerComponent<ComponentBehaviorTree>("BehaviorTree");
	registerComponent<ComponentPlanner>("Planner");

	registerComponent<ComponentLANReplication>("LANReplication");

	registerComponent<ComponentText>("Text");
	registerComponent<ComponentListener>("Listener");
	registerComponent<ComponentSoundBuffer>("SoundBuffer");
	registerComponent<ComponentTiledMap>("TiledMap");
	registerComponent<ComponentTransform>("Transform");

#ifndef SFGMKR_ANDROID
	registerComponent<ComponentShader>("Shader");
#endif
}