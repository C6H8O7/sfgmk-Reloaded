#ifndef SFGMKR_PLANNER_HPP
#define SFGMKR_PLANNER_HPP

#include "stdafx.h"

namespace gmk
{
	struct sPLANNER_BLACKBOARD_VALUE
	{
		r_string valueName;
		r_int32 valueData;

		sPLANNER_BLACKBOARD_VALUE(r_string _name = "NULL", r_int32 _data = 0)
			: valueName(_name), valueData(_data)
		{

		}
	};

	class Planner
	{
	public:

		Planner();
		~Planner();

		GMK_CLASS_PROPERTY_FUNCS(r_string, m_goal, Goal, r_void)

		r_void addAction(PlannerAction* _action);

		r_void addBlackboardValue(r_string _name);

		r_bool findPlan();
		r_bool findActionPlan(gmk::PlannerAction* _action);

		PlannerAction* findActionWithEffect(r_string _name, r_int32 _value);

		r_void update();

	protected:

		r_string m_goal = "NULL";
		r_int32 m_goalValue = 0;

		PlannerPlan m_plan;

		PlannerAction* m_currentAction = 0;
		
		gmk::vector<sPLANNER_BLACKBOARD_VALUE*> m_blackboard;
		gmk::vector<PlannerAction*> m_actions;
	};
}

#endif