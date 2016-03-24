collectDuration = 1.0; -- -public -float

timer = 0.0;

backpack = 0;

function OnStart()
	backpack = this.lua:getScript("backpack");
end

function OnUpdate()
	timer = timer + time.deltaTime;
	
	if(timer >= collectDuration) then
		timer = 0.0;
		currentOre = backpack:getInt("nbOre");
		currentOre = currentOre + 1;
		backpack:setInt("nbOre", currentOre);
	end
end