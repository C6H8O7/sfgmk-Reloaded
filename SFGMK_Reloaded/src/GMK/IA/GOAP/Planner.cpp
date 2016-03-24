#include "stdafx.h"

namespace gmk
{
	Planner::Planner()
	{

	}

	Planner::~Planner()
	{
		m_blackboard.deleteAndClear();
		m_actions.deleteAndClear();
	}

	r_void Planner::addAction(PlannerAction* _action)
	{
		_action->setPlanner(this);

		m_actions.push_back(_action);
	}

	r_void Planner::addBlackboardValue(r_string _name)
	{
		r_bool exists = false;

		for (r_uint32 i = 0; i < m_blackboard.size(); i++)
			if (m_blackboard[i]->valueName == _name)
				exists = true;

		if (!exists)
			m_blackboard.push_back(new sPLANNER_BLACKBOARD_VALUE(_name, 0));
	}

	r_bool Planner::findPlan()
	{
		m_plan.clear();

		PlannerAction* firstAction = findActionWithEffect(m_goal, m_goalValue);

		if (!firstAction)
			return false;

		m_plan.push_back(firstAction);

		if (!findActionPlan(firstAction)) {
			m_plan.clear();
			return false;
		}

		printf("plan found: %d actions\n", m_plan.size());

		return true;
	}

	r_bool Planner::findActionPlan(gmk::PlannerAction* _action)
	{
		if (!_action->needsSpecialCondition())
			return true;

		auto conditions = _action->getConditions();

		for (r_uint32 i = 0; i < conditions.size(); i++) {
			if (conditions[i]->value == 0)
				continue;

			PlannerAction* action = findActionWithEffect(conditions[i]->name, conditions[i]->value);
			if (action) {
				m_plan.push_back(action);
				findActionPlan(action);
				return true;
			}
		}

		return false;
	}

	PlannerAction* Planner::findActionWithEffect(r_string _name, r_int32 _value)
	{
		for (r_uint32 i = 0; i < m_actions.size(); i++) {
			sPLANNER_CONDITION_EFFECT* effect = m_actions[i]->findEffect(_name);
			if (effect && effect->value == _value)
				return m_actions[i];
		}

		return 0;
	}

	r_void Planner::update()
	{
		if (m_currentAction) {
			m_currentAction->perform();

			if (m_currentAction->isDone()) {
				m_currentAction = 0;
				m_plan.pop_back();

				if (m_plan.size()) {
					m_currentAction = m_plan[m_plan.size() - 1];
					m_currentAction->start();
				} else {
					findPlan();
				}
			}

		} else {
			findPlan();
		}
	}
}