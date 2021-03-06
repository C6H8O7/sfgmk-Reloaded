/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		22/02/2016
	@brief

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_COMPONENT_BEHAVIOR_TREE_HPP
#define SFGMKR_COMPONENT_BEHAVIOR_TREE_HPP

#include "stdafx.h"


class ComponentBehaviorTree : public GameObjectComponent
{
	public:
		ComponentBehaviorTree(GameObject* _parent);
		~ComponentBehaviorTree();

		virtual r_void OnUpdate(SFMLCanvas * _canvas);
		virtual r_void OnDraw(SFMLCanvas* _canvas);

		virtual r_void OnMembersUpdate();

	#ifdef SFGMKR_EDITOR
		virtual r_void OnRegistration();
	#endif

		virtual r_void OnXMLSave(tinyxml2::XMLElement* _element);
		virtual r_void OnXMLLoad(tinyxml2::XMLElement* _element);

	private:	
		gmk::BehaviorTree m_BehaviorTree;
};


#endif