beginX = 1138.0; -- -public -float
beginY = 160.0; -- -public -float
offsetY = 99.5; -- -public -float
maxY = 4; -- -public -int

cooldown = 8.0; -- -public -float

timer = 0.0;

isHost = 0;

function OnStart()
	isHost = net.isHost();
end

function OnUpdate()
	if (isHost == 1) then
		timer = timer + time.deltaTime;
		
		if (timer >= cooldown) then
			timer = 0.0;
			
			x = beginX;
			y = math.random(0, maxY) * offsetY + beginY;
		
			enemy = game.instantiate("circle");
			enemy.transform:setPosition(r_vector2f(x, y));
		end
	end
end