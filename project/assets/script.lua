function OnUpdate()
	this.transform.rotation = this.transform.rotation + 360.0 * time.deltaTime;
	if (input.mouse.right == 1) then
		game.loadScene("Default");
	end
end