amplitude = 20.0; -- -public -float
speed = 1.0; -- -public -float

timer = 0.0;

function OnUpdate()
	timer = timer + time.deltaTime;
	this.transform:setRotation(amplitude * math.sin(timer * speed));
end