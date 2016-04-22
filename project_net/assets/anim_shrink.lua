acceleration = 1.0; -- -public -float
v0 = 1.0; -- -public -float

v = 0.0;
a = 0.0;
scale = 0;

function OnStart()
	v = v0;
	a = acceleration;
	scale = this.transform:getScale();
end

function OnUpdate()
	a = a + acceleration * time.deltaTime;
	v = v + a * time.deltaTime;
	
	scale.x = scale.x - v * time.deltaTime;
	scale.y = scale.y - v * time.deltaTime;
	
	this.transform:setScale(scale);
	
	if (scale.x < 0.0 and scale.y < 0.0) then
		this.gameobject:destroy();
	end
end