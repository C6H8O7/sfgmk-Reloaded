#include "stdafx.h"


namespace gmk
{
	Behavior::Behavior() : m_Parent(NULL), m_Status(BH_NOT_INITIALISED)
	{
	}

	Behavior::~Behavior()
	{
	}


	r_void Behavior::reInit()
	{
		m_Status = BH_NOT_INITIALISED;
	}


	const eBEHAVIOR_STATUS& Behavior::process(const r_float& _DeltaTime)
	{
		m_Status < BEHAVIOR_FUNCTIONS_NUMBER ?
			m_Status = (this->*m_Functions[m_Status])(_DeltaTime)
			: m_Status;

		return m_Status;
	}


	const eBEHAVIOR_STATUS& Behavior::getStatus() const
	{
		return m_Status;
	}

	r_void Behavior::setParent(Behavior* _Parent)
	{
		m_Parent = _Parent;
	}
}