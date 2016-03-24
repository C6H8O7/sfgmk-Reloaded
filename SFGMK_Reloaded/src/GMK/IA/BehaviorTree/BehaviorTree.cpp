#include "stdafx.h"


namespace gmk
{
	BehaviorTree::BehaviorTree(Behavior* _Root) : m_Root(_Root)
	{
		m_CurrentBehavior.Status = BH_NOT_INITIALISED; 
		m_CurrentBehavior.BehaviorPtr = m_Root;
	}

	BehaviorTree::~BehaviorTree()
	{
		delete m_Root; 
	}


	r_void BehaviorTree::update(const r_float& _DeltaTime)
	{
		m_CurrentBehavior.Status = m_CurrentBehavior.BehaviorPtr->process(_DeltaTime);
	}


	r_void BehaviorTree::setRoot(Behavior* _Root)
	{
		m_Root = _Root;
	}

	r_void BehaviorTree::setCurrentBehavior(Behavior* _Node, const eBEHAVIOR_STATUS& _Status)
	{ 
		m_CurrentBehavior.BehaviorPtr = _Node;
		m_CurrentBehavior.Status = _Status; 
	}
}