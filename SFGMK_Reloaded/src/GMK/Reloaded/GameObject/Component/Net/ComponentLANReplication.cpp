#include "stdafx.h"

ComponentLANReplication::ComponentLANReplication(GameObject* _parent)
	: GameObjectComponent("LANReplication", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif

	srand(time(0));
	parent->networkID = rand() | (rand() << 16);
	gmk::net::NetworkManager::GetInstance()->registerGameObject(parent);
}

ComponentLANReplication::~ComponentLANReplication()
{
	gmk::net::NetworkManager::GetInstance()->unregisterGameObject(parent);
}

r_void ComponentLANReplication::OnUpdate(SFMLCanvas * _canvas)
{
	if (!_canvas->isPlaying)
		return;

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

	endRegister();
}
#endif

r_void ComponentLANReplication::OnXMLSave(tinyxml2::XMLElement* _element)
{
	_element->SetAttribute("tick", m_tick);
}

r_void ComponentLANReplication::OnXMLLoad(tinyxml2::XMLElement* _element)
{
	m_tick = _element->FloatAttribute("tick");
}