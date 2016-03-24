#ifndef SFGMKR_PLANNER_ACTION
#define SFGMKR_PLANNER_ACTION

#include "stdafx.h"

namespace gmk
{
	class Lua;
	class Planner;

	struct sPLANNER_CONDITION_EFFECT
	{
		r_string name;
		r_int32 value;

		sPLANNER_CONDITION_EFFECT(r_string _name = "NULL", r_int32 _value = 0)
			: name(_name), value(_value)
		{

		}
	};

	class PlannerAction
	{
	public:

		PlannerAction(gmk::Lua* _lua);
		~PlannerAction();

		r_void addCondition(r_string _name, r_int32 _value);
		r_void addEffect(r_string _name, r_int32 _value);

		r_void start();
		r_bool perform();

		r_bool needsSpecialCondition();

		sPLANNER_CONDITION_EFFECT* findCondition(r_string _name);
		sPLANNER_CONDITION_EFFECT* findEffect(r_string _name);

		gmk::vector<sPLANNER_CONDITION_EFFECT*>& getConditions();
		gmk::vector<sPLANNER_CONDITION_EFFECT*>& getEffects();

		r_void setPlanner(gmk::Planner* _planner);

		r_bool isDone();

	protected:

		r_bool m_isDone = false;

		gmk::vector<sPLANNER_CONDITION_EFFECT*> m_conditions;
		gmk::vector<sPLANNER_CONDITION_EFFECT*> m_effects;

		gmk::Lua* m_lua = 0;

		gmk::Planner* m_planner = 0;
	};

	typedef gmk::vector<PlannerAction*> PlannerPlan;
}

#endif