#include "stdafx.h"


namespace gmk
{
	BehaviorTreeRepeater::BehaviorTreeRepeater(const r_bool& _IsInfinite, const r_uint32& _RepeatNumber) : m_bIsInfinite(_IsInfinite), m_uiRepeatNumber(_RepeatNumber), m_uiActualRepeat(0U)
	{
	}

	BehaviorTreeRepeater::~BehaviorTreeRepeater()
	{
	}


	r_void BehaviorTreeRepeater::reInit()
	{
		Behavior::reInit();
		m_uiActualRepeat = 0U;
	}


	const eBEHAVIOR_STATUS& BehaviorTreeRepeater::initialise(const r_float& _DeltaTime)
	{
		std::cout << "Repeater initialise" << std::endl;
		m_Status = BH_RUNNING;
		return m_Status;
	}

	const eBEHAVIOR_STATUS& BehaviorTreeRepeater::update(const r_float& _DeltaTime)
	{
		std::cout << "Repeater Update: " << m_uiActualRepeat << " iteration" << std::endl;

		m_ChildStatus = m_Child->process(_DeltaTime);

		if( m_ChildStatus > BH_TERMINATING )
		{
			reInitChild();
			m_uiActualRepeat++;
		}

		if( !m_bIsInfinite && !(m_uiActualRepeat < m_uiRepeatNumber) )
			m_Status = BH_TERMINATING;

		return m_Status;
	}

	const eBEHAVIOR_STATUS& BehaviorTreeRepeater::terminate(const r_float& _DeltaTime)
	{
		std::cout << "Repeater terminate" << std::endl;
		m_Status = BH_SUCCESS;
		return m_Status;
	}
}