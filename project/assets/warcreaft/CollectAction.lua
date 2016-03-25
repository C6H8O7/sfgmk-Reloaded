Range = 0.0; -- -public -float
DepositDuration = 0.0;  -- -public -float

Bank = 0;
BankBackpack = 0;

Condition = ""; -- -public -string
Effect = ""; -- -public -string
Objective = ""; -- -public -string

BankValue = ""; -- -public -string

timer = 0.0;

function OnStart()
	action = this.planner:createAction(this.lua);
	action:addCondition(Condition, 1);
	action:addEffect(Effect, 0);
	action:addEffect(Objective, 1);
	
	this.planner:addAction(action);
end

function OnPlannerActionStart(_action)
	Bank = game.getGameObjectByName("Bank");
	BankBackpack = Bank:getScript("backpack");
	this.steering:setTarget("SteeringArrival", Bank);
	timer = 0.0;
end

function OnPlannerActionPerform(_action)
	myPos = this.transform:getPosition();
	bankPos = Bank.transform:getPosition();
	
	distance = math.distance(myPos, bankPos);

	if (distance <= Range) then
		this.rigidbody:cleanSpeed();
		timer = timer + time.deltaTime;
		if (timer >= DepositDuration) then
			current = BankBackpack:getInt(BankValue);
			current = current + 1;
			BankBackpack:setInt(BankValue, current);
			_action:setDone();
		end
	end
end