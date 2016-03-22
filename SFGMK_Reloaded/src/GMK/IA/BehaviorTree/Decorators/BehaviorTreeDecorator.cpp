#include "stdafx.h"


namespace gmk
{
	BehaviorTreeDecorator::BehaviorTreeDecorator() : m_ChildStatus(BH_NOT_INITIALISED) 
	{
	}

	BehaviorTreeDecorator::~BehaviorTreeDecorator() 
	{ 
		SAFE_DELETE(m_Child); 
	}


	r_void BehaviorTreeDecorator::reInit()
	{
		Behavior::reInit();
		m_ChildStatus = BH_NOT_INITIALISED;
	}

	r_void BehaviorTreeDecorator::reInitChild()
	{
		m_Child->reInit();
	}


	r_void BehaviorTreeDecorator::addChild(Behavior* _Node)
	{ 
		m_Child = _Node; 
		m_Child->setParent(this); 
	}
}