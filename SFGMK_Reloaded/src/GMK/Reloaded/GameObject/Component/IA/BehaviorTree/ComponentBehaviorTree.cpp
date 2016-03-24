#include "stdafx.h"


ComponentBehaviorTree::ComponentBehaviorTree(GameObject * _parent)
	: GameObjectComponent("BehaviorTree", _parent)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentBehaviorTree::~ComponentBehaviorTree()
{
}


r_void ComponentBehaviorTree::OnUpdate(SFMLCanvas * _canvas)
{
	if( _canvas->isPlaying )
		m_BehaviorTree.update(gmk::TimeManager::GetSingleton()->getDeltaTime());
}

r_void ComponentBehaviorTree::OnDraw(SFMLCanvas* _canvas)
{
}


r_void ComponentBehaviorTree::OnMembersUpdate()
{
}


#ifdef SFGMKR_EDITOR
r_void ComponentBehaviorTree::OnRegistration()
{
	beginRegister();

	endRegister();
}
#endif


r_void ComponentBehaviorTree::OnXMLSave(tinyxml2::XMLElement* _element)
{
}

r_void ComponentBehaviorTree::OnXMLLoad(tinyxml2::XMLElement* _element)
{
}