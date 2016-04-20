speed = 0.0; -- -public -float

function OnUpdate()
	currentRotation = this.transform:getRotation() + speed * time.deltaTime;
	currentRotation = currentRotation - math.floor(currentRotation / 360.0) * 360.0;
	this.transform:setRotation(currentRotation);
end