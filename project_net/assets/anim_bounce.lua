position0 = 0;
scale0 = 0;
timer = 0.0;

function OnStart()
	position0 = this.transform:getPosition();
	scale0 = this.transform:getScale();
end

function OnUpdate()
	timer = timer + time.deltaTime * 1000.0;
	ct = timer - math.floor(timer / 1000.0) * 1000.0;
	
	scaleX = 1.0;
	scaleY = 1.0;
	offsetY = 0.0;
	
	if (ct < 600) then
		scaleX = 1.0;
		scaleY = 1.0;
	elseif (ct < 800) then
		scaleX = 1.0 + (ct - 600) / 200.0 * 0.3;
		scaleY = 1.0 - (ct - 600) / 200.0 * 0.3;
	elseif (ct < 1000) then
		scaleX = 1.0 + 0.3 - (ct - 800) / 200.0 * 0.3;
		scaleY = 1.0 - 0.3 + (ct - 800) / 200.0 * 0.3;
	end
	
	if (ct < 300) then
		offsetY = ct / 300.0 * 10.0;
	elseif(ct < 600) then
		offsetY = 10.0 - (ct - 300) / 300.0 * 10.0;
	elseif (ct < 800) then
		offsetY = 0.0 - (ct - 600) / 200.0 * 8.4;
	elseif (ct < 1000) then
		offsetY = 0.0 - 8.4 + (ct - 800) / 200.0 * 8.4;
	end
	
	currentPosition = this.transform:getPosition();
	positionf = r_vector2f(currentPosition.x, position0.y - offsetY);
	this.transform:setPosition(positionf);
	
	this.transform:setScale(r_vector2f(scale0.x * scaleX, scale0.y * scaleY));
end