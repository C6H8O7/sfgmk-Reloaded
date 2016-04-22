life = 0; -- -public -int

function OnUpdate()
	if (life <= 0) then
		this.gameobject:destroy();
		proc_death = game.instantiate("proc_death");
		proc_death.transform:setPosition(this.transform:getPosition());
	end
end