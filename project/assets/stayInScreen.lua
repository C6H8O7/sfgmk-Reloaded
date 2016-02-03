_ScreenX = 1280; -- -public -float
_ScreenY = 720; -- -public -float

function OnUpdate()
	--X
	if this.transform.position.x < 0.0 then
		 this.rigidbody:setPosition(gmk.Vector2f(_ScreenX, this.transform.position.y));
	elseif this.transform.position.x > _ScreenX then
		 this.rigidbody:setPosition(gmk.Vector2f(0.0, this.transform.position.y));
	end

	--Y
	if this.transform.position.y < 0.0 then
		 this.rigidbody:setPosition(gmk.Vector2f(this.transform.position.x, _ScreenY));
	elseif this.transform.position.y > _ScreenY then
		 this.rigidbody:setPosition(gmk.Vector2f(this.transform.position.x, 0.0));
	end
end