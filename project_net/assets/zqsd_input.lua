function OnUpdate()

	currentPosition = this.transform:getPosition();
	if(input.keyboard.getKeyState(input.key.Z) == input.pressed) then
		debug.log("Z");
		currentPosition.y = currentPosition.y - 10;
	end
	if(input.keyboard.getKeyState(input.key.Q) == input.pressed) then
		debug.log("Q");
		currentPosition.x = currentPosition.x - 10;
	end
	if(input.keyboard.getKeyState(input.key.S) == input.pressed) then
		debug.log("S");
		currentPosition.y = currentPosition.y + 10;
	end
	if(input.keyboard.getKeyState(input.key.D) == input.pressed) then
		debug.log("D");
		currentPosition.x = currentPosition.x + 10;
	end
	this.transform:setPosition(currentPosition);
	
	if(input.keyboard.getKeyState(input.key.E) == input.down) then
		debug.log("E DOWN");
	end
end