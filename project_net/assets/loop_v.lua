speed = 100.0; -- -public -float
height = 720.0; -- -public -float
ny = 720.0; -- -public -float

function OnUpdate()
	currentPos = this.transform:getPosition();
	currentPos.y = currentPos.y - speed * time.deltaTime;
	this.transform:setPosition(currentPos);
	
	if currentPos.y <= -height then
		currentPos.y = ny;
		this.transform:setPosition(currentPos);
	end
end