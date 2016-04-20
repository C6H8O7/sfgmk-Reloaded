speed = 100.0; -- -public -float
width = 1280.0; -- -public -float
nx = 1280.0; -- -public -float

function OnUpdate()
	currentPos = this.transform:getPosition();
	currentPos.x = currentPos.x - speed * time.deltaTime;
	this.transform:setPosition(currentPos);
	
	if currentPos.x <= -width then
		currentPos.x = nx;
		this.transform:setPosition(currentPos);
	end
end