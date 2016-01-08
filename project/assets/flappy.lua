gfactor = 100.0;
g = 9.81 * gfactor;

ay = 0.0;
vy = 0.0;

vymax = 300.0;
vymin = -300.0;

x0 = 200.0;
y0 = 350.0;

fay = 275.0;
fvy = 100.0;

function gameover()
	this.transform.position.x = x0;
	this.transform.position.y = y0;
	ay = 0.0;
	vy = 0.0;
end

function physic()
	ay = ay + g * time.deltaTime;
	vy = vy + ay * time.deltaTime;
	
	if vy > vymax then
		vy = vymax;
	end
	if vy < vymin then
		vy = vymin;
	end
	
	this.transform.position.y = this.transform.position.y + vy * time.deltaTime;
end

function playerInput()
	if (input.mouse.left == 1) then
		ay = -fay;
		vy = -fvy;
	end
end

function OnUpdate()
	playerInput();
	physic();
	
	if this.transform.position.y > 720.0 then
		gameover();
	end
	
	this.transform.rotation = vy / vymax * 45.0;
end

function OnPhysicCollision(_wall)
	gameover();
end