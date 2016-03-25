Range = 0.0; -- -public -float
Duration = 0.0;  -- -public -float

BatimentName = ""; -- -public -string

Condition = ""; -- -public -string
Effect = ""; -- -public -string

Batiment = 0;

timer = 0.0;

function OnStart()
	action = this.planner:createAction(this.lua);
	action:addCondition(Condition, 0);
	action:addEffect(Effect, 1);
	
	this.planner:addAction(action);
end

function OnPlannerActionStart(_action)
	Batiment = game.getGameObjectByName(BatimentName);
	this.steering:setTarget("SteeringArrival", Batiment);
	timer = 0.0;
end

function OnPlannerActionPerform(_action)
	myPos = this.transform:getPosition();
	batimentPos = Batiment.transform:getPosition();
	
	distance = math.distance(myPos, batimentPos);
	
	if (distance <= Range) then
		this.rigidbody:cleanSpeed();
		timer = timer + time.deltaTime;
		if (timer >= Duration) then
			_action:setDone();
		end
	end
end