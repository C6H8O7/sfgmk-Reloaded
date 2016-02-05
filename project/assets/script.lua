function OnUpdate()
	this.transform:setRotation(this.transform:getRotation() + 360.0 * time.deltaTime);
	if (input.mouse.right == 1) then
		game.loadScene("Default");
	end
end