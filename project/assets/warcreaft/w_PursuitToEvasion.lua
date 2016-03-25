Duration = 5.0; -- -public -float
timer = 0.0;


function OnStart()

	action = this.planner:createAction(this.lua);
	action:addCondition("Pursuit", 1);
	action:addEffect("Evasion", 1);
	action:addEffect("Pursuit", 0);
	
	this.planner:addAction(action);

end

function OnPlannerActionStart(_action)
	timer = 0.0;
end

function OnPlannerActionPerform(_action)
	
	timer = timer + time.deltaTime;
	if (timer >= Duration) then
		_action:setDone();
		this.steering:setWeight("SteeringPursuit", 0.0);
		this.steering:setWeight("SteeringEvasion", 5.0);
	end

end