cooldown = 20.0; -- -public -float

timer = 0.0;
moneyScript = 0;

function OnStart()
	timer = 0.0;
	moneyScript = game.getGameObjectByName("money"):getScript("money");
end

function OnUpdate()
	timer = timer + time.deltaTime;
	
	if (timer >= cooldown) then
		timer = 0.0;
		moneyScript:callFunction("triangleProc");
		net.sendGameObjectCall("money", "money", "triangleProc");
		
		proc_triangle = game.instantiate("proc_triangle");
		proc_triangle.transform:setPosition(this.transform:getPosition());
	end
end