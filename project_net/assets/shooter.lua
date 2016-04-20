bulletType = ""; -- -public -string
cooldown = 1.0; -- -public -float

timer = 0.0;

function OnStart()
	timer = 0.0;
end

function OnUpdate()
	timer = timer + time.deltaTime;
	
	if (timer >= cooldown) then
		timer = 0.0;
		bullet = game.instantiate(bulletType);
		bullet.transform:setPosition(this.transform:getPosition());
	end
end