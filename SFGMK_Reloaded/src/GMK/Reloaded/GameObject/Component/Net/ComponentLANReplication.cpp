#include "stdafx.h"

ComponentLANReplication::ComponentLANReplication(GameObject* _parent)
	: GameObjectComponent("LANReplication", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	parent->networkID = NETWORK_RANDOM;
}

ComponentLANReplication::~ComponentLANReplication()
{
	gmk::net::NetworkManager* manager = gmk::net::NetworkManager::GetInstance();

	manager->unregisterGameObject(parent);
	manager->sendState(parent, gmk::net::PacketHandling::Dead);
}

r_void ComponentLANReplication::OnUpdate(SFMLCanvas * _canvas)
{
	if (!_canvas->isPlaying)
		return;

	if (!m_registered)
		registerNetwork(true);

	m_timer += gmk::TimeManager::GetSingleton()->getDeltaTime();

	if (m_timer > m_tick)
	{
		m_timer = 0.0f;
		gmk::net::NetworkManager::GetInstance()->sendUpdate(parent);
	}
}

r_void ComponentLANReplication::OnDraw(SFMLCanvas* _canvas)
{

}

r_void ComponentLANReplication::OnMembersUpdate()
{

}

#ifdef SFGMKR_EDITOR
r_void ComponentLANReplication::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_FLOAT, "Tick", &m_tick);

	GameObjectComponent::ComponentProperty* propertyType = registerProperty(ePROPERTY_TYPE::TYPE_ENUM, "Proprietary", &parent->networkPropType);
	propertyType->wxChoices.Add("Instancier", gmk::net::PacketHandling::GameObjectStateProp::Instancier);
	propertyType->wxChoices.Add("Host", gmk::net::PacketHandling::GameObjectStateProp::Host);

	endRegister();
}
#endif

r_void ComponentLANReplication::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("tick", m_tick);
	_element->SetAttribute("prop", parent->networkPropType);
}

r_void ComponentLANReplication::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_tick = _element->FloatAttribute("tick");
	parent->networkPropType = (gmk::net::PacketHandling::GameObjectStateProp)_element->IntAttribute("prop");
}

r_void ComponentLANReplication::registerNetwork(r_bool _sendState)
{
	m_registered = true;

	gmk::net::NetworkManager* manager = gmk::net::NetworkManager::GetInstance();
	manager->registerGameObject(parent);

	if (_sendState)
		manager->sendState(parent, gmk::net::PacketHandling::Alive);

	if (parent->networkPropType == gmk::net::PacketHandling::GameObjectStateProp::Host && !manager->IsHost())
		parent->networkProp = 1;
}