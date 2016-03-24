#include "stdafx.h"

namespace gmk
{
	PlannerAction::PlannerAction(gmk::Lua* _lua)
		: m_lua(_lua)
	{

	}

	PlannerAction::~PlannerAction()
	{
		m_conditions.deleteAndClear();
		m_effects.deleteAndClear();
	}

	r_void PlannerAction::addCondition(r_string _name, r_int32 _value)
	{
		if (m_planner)
		{
			m_planner->addBlackboardValue(_name);
			m_conditions.push_back(new sPLANNER_CONDITION_EFFECT(_name, _value));
		}
	}

	r_void PlannerAction::addEffect(r_string _name, r_int32 _value)
	{
		if (m_planner)
		{
			m_planner->addBlackboardValue(_name);
			m_effects.push_back(new sPLANNER_CONDITION_EFFECT(_name, _value));
		}
	}

	r_void PlannerAction::start()
	{
		m_isDone = false;

		m_lua->onPlannerActionStart(this);
	}

	r_bool PlannerAction::perform()
	{
		m_lua->onPlannerActionPerform(this);

		return m_isDone;
	}

	r_bool PlannerAction::needsSpecialCondition()
	{
		for (r_uint32 i = 0; i < m_conditions.size(); i++)
			if (m_conditions[i]->value > 0)
				return true;

		return false;
	}

	sPLANNER_CONDITION_EFFECT* PlannerAction::findCondition(r_string _name)
	{
		for (r_uint32 i = 0; i < m_conditions.size(); i++)
			if (m_conditions[i]->name == _name)
				return m_conditions[i];

		return 0;
	}

	sPLANNER_CONDITION_EFFECT* PlannerAction::findEffect(r_string _name)
	{
		for (r_uint32 i = 0; i < m_effects.size(); i++)
			if (m_effects[i]->name == _name)
				return m_effects[i];

		return 0;
	}

	gmk::vector<sPLANNER_CONDITION_EFFECT*>& PlannerAction::getConditions()
	{
		return m_conditions;
	}

	gmk::vector<sPLANNER_CONDITION_EFFECT*>& PlannerAction::getEffects()
	{
		return m_effects;
	}

	r_void PlannerAction::setPlanner(gmk::Planner* _planner)
	{
		m_planner = _planner;
	}

	r_bool PlannerAction::isDone()
	{
		return m_isDone;
	}
}