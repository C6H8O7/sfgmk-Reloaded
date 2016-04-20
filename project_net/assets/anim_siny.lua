speed = 0.0; -- -public -float
amplitude = 0.0; -- -public -float

position0 = 0;
timer = 0.0;

function OnStart()
	position0 = this.transform:getPosition();
end

function OnUpdate()
	timer = timer + time.deltaTime;
	offsetY = amplitude * math.sin(timer * speed);
	currentPosition = this.transform:getPosition();
	this.transform:setPosition(r_vector2f(currentPosition.x, position0.y + offsetY));
end