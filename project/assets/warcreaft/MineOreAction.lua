function OnStart()
	action = PlannerAction(this.lua);
	action:addEffect("hasOre", 1);
	this.planner:addAction(action);
end

function OnPlannerActionStart(_action)

end

function OnPlannerActionPerform(_action)

end