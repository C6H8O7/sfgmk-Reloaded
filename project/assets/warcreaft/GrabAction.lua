Speed = 0.0; -- -public -float
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
	timer = 0.0;
end

function OnPlannerActionPerform(_action)
	myPos = this.transform:getPosition();
	batimentPos = Batiment.transform:getPosition();
	
	distance = math.distance(myPos, batimentPos);
	
	if (distance > Range) then
		unitVector = math.unitVectorFromPoints(myPos, batimentPos);
		myPos.x = myPos.x + unitVector.x * Speed * time.deltaTime;
		myPos.y = myPos.y + unitVector.y * Speed * time.deltaTime;
		this.transform:setPosition(myPos);
	else
		timer = timer + time.deltaTime;
		if (timer >= Duration) then
			_action:setDone();
		end
	end
end