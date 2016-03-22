#include "stdafx.h"


namespace gmk
{
	BehaviorTreeSequence::BehaviorTreeSequence() : m_uiSequenceLength(0U), m_uiSequenceCurrentPosition(0U), m_fTaskTime(0.0f), m_CurrentPositionStatus(BH_NOT_INITIALISED)
	{
	}

	BehaviorTreeSequence::~BehaviorTreeSequence()
	{
	}


	r_void BehaviorTreeSequence::reInit()
	{
		Behavior::reInit();
		reInitChilds();
		m_uiSequenceCurrentPosition = 0U;
		m_fTaskTime = 0.0f;
		m_Status = m_CurrentPositionStatus = BH_NOT_INITIALISED;
	}


	const eBEHAVIOR_STATUS& BehaviorTreeSequence::initialise(const r_float& _DeltaTime)
	{
		std::cout << "Sequence initialise" << std::endl;
		m_Status = BH_RUNNING;
		return m_Status;
	}

	const eBEHAVIOR_STATUS& BehaviorTreeSequence::update(const r_float& _DeltaTime)
	{
		std::cout << "Sequence update" << std::endl;
		std::cout << m_fTaskTime << "    current task: " << m_uiSequenceCurrentPosition << std::endl;

		m_fTaskTime += _DeltaTime;
		m_CurrentPositionStatus = m_Childs[m_uiSequenceCurrentPosition]->process(_DeltaTime);

		if( m_CurrentPositionStatus > BH_TERMINATING )
		{
			m_fTaskTime = 0.0f;
			m_uiSequenceCurrentPosition++;
		}

		if( !(m_uiSequenceCurrentPosition < m_uiSequenceLength) )
			m_Status = BH_TERMINATING;

		return m_Status;
	}

	const eBEHAVIOR_STATUS& BehaviorTreeSequence::terminate(const r_float& _DeltaTime)
	{
		std::cout << "Sequence terminate" << std::endl;
		m_Status = BH_SUCCESS;
		return m_Status;
	}


	r_void BehaviorTreeSequence::addChild(Behavior* _Node)
	{ 
		m_Childs.push_back(_Node); 
		_Node->setParent(this); 
		m_uiSequenceLength++; 
	}
}