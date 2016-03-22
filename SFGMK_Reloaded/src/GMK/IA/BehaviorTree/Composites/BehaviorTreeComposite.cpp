#include "stdafx.h"


namespace gmk
{
	BehaviorTreeComposite::BehaviorTreeComposite()
	{
	}

	BehaviorTreeComposite::~BehaviorTreeComposite()
	{ 
		m_Childs.deleteAndClear(); 
	}


	r_void BehaviorTreeComposite::reInitChilds()
	{
		for( r_uint32 i(0U); i < m_Childs.size(); i++ )
			m_Childs[i]->reInit();
	}


	r_void BehaviorTreeComposite::addChild(Behavior* _Node)
	{ 
		m_Childs.push_back(_Node); 
		_Node->setParent(this);
	}
}