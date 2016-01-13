x0 = 200.0; -- -public -float
y0 = 350.0; -- -public -float

fay = 275.0; -- -public -float
fvy = 100.0; -- -public -float

function gameover()
	this.rigidbody:setPosition(gmk.Vector2f(x0, y0));
	this.rigidbody:cleanForces();
	this.rigidbody:cleanSpeed();
end

function playerInput()
	if (input.mouse.left == 1) then
		this.rigidbody:setForce(gmk.Vector2f(0.0, -fay));
		this.rigidbody:setSpeed(gmk.Vector2f(0.0, -fvy));
	end
end

function OnUpdate()
	playerInput();
	
	if this.transform.position.y > 720.0 then
		gameover();
	end
	
	this.transform.rotation = this.rigidbody:getSpeed().y / this.rigidbody:getMaxSpeed() * 45.0;
end

function OnPhysicCollision(_wall)
	gameover();
end