beginX = 0.0; -- -public -float
beginY = 0.0; -- -public -float
offsetY = 0.0; -- -public -float
selectionCount = 2; -- -public -int

selection = 0;

function OnUpdate()
	if (input.keyboard.getKeyState(input.key.Z) == input.pressed) then
		selection = selection - 1;
	end
	if (input.keyboard.getKeyState(input.key.S) == input.pressed) then
		selection = selection + 1;
	end
	
	if (selection > selectionCount) then
		selection = 0;
	elseif (selection < 0) then
		selection = selectionCount;
	end

	this.transform:setPosition(r_vector2f(beginX, beginY + selection * offsetY));
	
	if (input.keyboard.getKeyState(input.key.P) == input.pressed) then
		if (selection == 0) then
			net.setClient();
			game.loadScene("Default");
		elseif (selection == 1) then
			net.setHost();
			game.loadScene("Default");
		else
			debug.log("exit");
		end
	end
end