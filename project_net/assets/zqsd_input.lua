function OnUpdate()
	if(input.keyboard.getKeyState(input.key.Z) == input.pressed) then
		debug.log("Z");
	end
	if(input.keyboard.getKeyState(input.key.Q) == input.pressed) then
		debug.log("Q");
	end
	if(input.keyboard.getKeyState(input.key.S) == input.pressed) then
		debug.log("S");
	end
	if(input.keyboard.getKeyState(input.key.D) == input.pressed) then
		debug.log("D");
	end
	if(input.keyboard.getKeyState(input.key.E) == input.down) then
		debug.log("E DOWN");
	end
end