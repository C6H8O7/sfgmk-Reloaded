#include "stdafx.h"


namespace gmk
{
	BehaviorTreeLeaf::BehaviorTreeLeaf()
	{
	}

	BehaviorTreeLeaf::~BehaviorTreeLeaf()
	{
	}


	const eBEHAVIOR_STATUS& BehaviorTreeLeaf::initialise(const r_float& _DeltaTime)
	{
		std::cout << "Leaf initialise" << std::endl;
		m_Status = BH_RUNNING;
		return m_Status;
	}

	const eBEHAVIOR_STATUS& BehaviorTreeLeaf::update(const r_float& _DeltaTime)
	{
		std::cout << "Leaf Update" << std::endl;
		m_Status = BH_TERMINATING;
		return m_Status;
	}

	const eBEHAVIOR_STATUS& BehaviorTreeLeaf::terminate(const r_float& _DeltaTime)
	{
		std::cout << "Leaf terminate" << std::endl;
		m_Status = BH_SUCCESS;
		return m_Status;
	}
}