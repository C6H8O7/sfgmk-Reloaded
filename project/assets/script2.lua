function OnStart()
	p0 = r_vectorf2(this.transform:getPosition());
end

function OnUpdate()
	this.transform:setPosition(p0.x + 50.0 * math.cos(time.totalTime), p0.y + 50.0 * math.sin(time.totalTime));
end