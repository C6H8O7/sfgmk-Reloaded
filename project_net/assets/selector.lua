beginX = 242.0; -- -public -float
beginY = 160.0; -- -public -float
offsetX = 99.5; -- -public -float
offsetY = 99.5; -- -public -float
maxX = 8; -- -public -int
maxY = 4; -- -public -int

squarePrice = 100; -- -public -int
trianglePrice = 50; -- -public -int
rectanglePrice = 50; -- -public -int

currentX = 0;
currentY = 0;

currentSelection = nil;

moneyScript = 0;

function OnStart()
	moneyScript = game.getGameObjectByName("money"):getScript("money");
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
		currentMoney = moneyScript:getInt("money");
		if (currentSelection == nil and currentMoney >= squarePrice) then
			currentMoney = currentMoney - squarePrice;
			square = game.instantiate("square");
			square.transform:setPosition(this.transform:getPosition());
			moneyScript:setInt("money", currentMoney);
		end
	end

	if (input.keyboard.getKeyState(input.key.U) == input.pressed) then
		currentMoney = moneyScript:getInt("money");
		if (currentSelection == nil and currentMoney >= trianglePrice) then
			currentMoney = currentMoney - trianglePrice;
			triangle = game.instantiate("triangle");
			triangle.transform:setPosition(this.transform:getPosition());
			moneyScript:setInt("money", currentMoney);
		end
	end
	
	if (input.keyboard.getKeyState(input.key.I) == input.pressed) then
		currentMoney = moneyScript:getInt("money");
		if (currentSelection == nil and currentMoney >= rectanglePrice) then
			currentMoney = currentMoney - rectanglePrice;
			rectangle = game.instantiate("rectangle");
			rectangle.transform:setPosition(this.transform:getPosition());
			moneyScript:setInt("money", currentMoney);
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
end

function OnPhysicEnter()
	currentSelection = nil;
end

function OnPhysicCollision(_collider)
	if (_collider.tag == "player") then
		currentSelection = _collider;
	end
end