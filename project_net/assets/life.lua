life = 0; -- -public -int

function OnUpdate()
	if (life <= 0) then
		this.gameobject:destroy();
	end
end