beginX = 242.0; -- -public -float
beginY = 160.0; -- -public -float
offsetX = 99.5; -- -public -float
offsetY = 99.5; -- -public -float
maxX = 8; -- -public -int
maxY = 4; -- -public -int

money = 1000; -- -public -int

squarePrice = 100; -- -public -int
trianglePrice = 50; -- -public -int

currentX = 0;
currentY = 0;

currentSelection = nil;

-- money
timerMoney = 0.0;
cooldownMoney = 10.0; -- -public -float
automoneyAmount = 25; -- -public -int

function updateMoney()
	timerMoney = timerMoney + time.deltaTime;
	
	if (timerMoney >= cooldownMoney) then
		timerMoney = 0.0;
		money = money + automoneyAmount;
	end
end

function OnUpdate()
	if (input.keyboard.getKeyState(input.key.Z) == input.pressed) then
		currentY = currentY - 1;
	end
	if (input.keyboard.getKeyState(input.key.S) == input.pressed) then
		currentY = currentY + 1;
	end
	if (input.keyboard.getKeyState(input.key.Q) == input.pressed) then
		currentX = currentX - 1;
	end
	if (input.keyboard.getKeyState(input.key.D) == input.pressed) then
		currentX = currentX + 1;
	end
	
	if (input.keyboard.getKeyState(input.key.Y) == input.pressed) then
		if (currentSelection == nil and money >= squarePrice) then
			money = money - squarePrice;
			square = game.instantiate("square");
			square.transform:setPosition(this.transform:getPosition());
		end
	end

	if (input.keyboard.getKeyState(input.key.U) == input.pressed) then
		if (currentSelection == nil and money >= trianglePrice) then
			money = money - trianglePrice;
			square = game.instantiate("triangle");
			square.transform:setPosition(this.transform:getPosition());
		end
	end
	
	if (input.keyboard.getKeyState(input.key.M) == input.pressed) then
		if (currentSelection ~= nil) then
			currentSelection:hardDestroy();
			currentSelection = nil;
		end
	end
	
	if (currentX > maxX) then
		currentX = 0;
	elseif (currentX < 0) then
		currentX = maxX;
	end
	
	if (currentY > maxY) then
		currentY = 0;
	elseif (currentY < 0) then
		currentY = maxY;
	end

	this.transform:setPosition(r_vector2f(beginX + currentX * offsetX, beginY + currentY * offsetY));
	
	updateMoney();
end

function OnPhysicEnter()
	currentSelection = nil;
end

function OnPhysicCollision(_collider)
	if (_collider.tag == "player") then
		currentSelection = _collider;
	end
end