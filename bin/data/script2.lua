x0 = 0;
y0 = 0;

function OnStart()
	x0 = transform.position.x;
	y0 = transform.position.y;
end

function OnUpdate()
	transform.position.x = x0 + 50.0 * math.cos(time.totalTime);
	transform.position.y = y0 + 50.0 * math.sin(time.totalTime);
end