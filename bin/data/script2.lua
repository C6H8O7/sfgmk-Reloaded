x0 = 0;
y0 = 0;

function OnStart()
	x0 = this.transform.position.x;
	y0 = this.transform.position.y;
end

function OnUpdate()
	this.transform.position.x = x0 + 50.0 * math.cos(time.totalTime);
	this.transform.position.y = y0 + 50.0 * math.sin(time.totalTime);
end