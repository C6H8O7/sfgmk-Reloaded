_ScreenX = 1280; -- -public -float
_ScreenY = 720; -- -public -float

function OnUpdate()
	currentPos = this.transform:getPosition();
	
	--X
	if currentPos.x < 0.0 then
		 this.rigidbody:setPosition(r_vector2f(_ScreenX, currentPos.y));
	elseif currentPos.x > _ScreenX then
		 this.rigidbody:setPosition(r_vector2f(0.0, currentPos.y));
	end
	
	currentPos = this.transform:getPosition();

	--Y
	if currentPos.y < 0.0 then
		 this.rigidbody:setPosition(r_vector2f(currentPos.x, _ScreenY));
	elseif currentPos.y > _ScreenY then
		 this.rigidbody:setPosition(r_vector2f(currentPos.x, 0.0));
	end
end