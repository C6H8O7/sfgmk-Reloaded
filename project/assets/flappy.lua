x0 = 200.0; -- -public -float
y0 = 350.0; -- -public -float

fay = 275.0; -- -public -float
fvy = 100.0; -- -public -float

score = 0;
scoreText = 0;
soundBufferScore = 0;

function updateScore()
	scoreText.text = string.format("%s %i", "SCORE :", score);
end

function gameover()
	this.rigidbody:setPosition(gmk.Vector2f(x0, y0));
	this.rigidbody:cleanForces();
	this.rigidbody:cleanSpeed();
	
	score = 0;
	updateScore(score);
end

function playerInput()
	if (input.mouse.left == 1) then
		this.rigidbody:setForce(gmk.Vector2f(0.0, -fay));
		this.rigidbody:setSpeed(gmk.Vector2f(0.0, -fvy));
		this.soundBuffer:playSound();
	end
	if (input.mouse.right == 1) then
		game.loadScene("Goombas");
	end
end

function OnStart()
	scoreText = game.getGameObjectByName("scoretext");
	soundBufferScore = game.getGameObjectByName("SoundBufferScore");
end

function OnUpdate()
	playerInput();
	
	if this.transform.position.y > 720.0 then
		gameover();
	end
	
	this.transform.rotation = this.rigidbody:getSpeed().y / this.rigidbody:getMaxSpeed() * 45.0;
end

function OnPhysicCollisionEnter(_collider)
	if(_collider.tag == "score") then
		score = score + 1;
		updateScore(score);
		soundBufferScore.soundBuffer:playSound();
	end
end

function OnPhysicCollision(_collider)
	if(_collider.tag == "wall") then
		gameover();
	end
end