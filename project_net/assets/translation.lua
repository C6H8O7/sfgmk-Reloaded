speed = 100.0; -- -public -float

enabled = 1; -- -public -int

function OnUpdate()
	if (enabled == 1) then
		currentPos = this.transform:getPosition();
		currentPos.x = currentPos.x + speed * time.deltaTime;
		this.transform:setPosition(currentPos);
	end
end