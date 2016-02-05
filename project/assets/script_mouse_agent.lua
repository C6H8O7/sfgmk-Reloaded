function OnUpdate()
	if input.mouse.right == 1 then
		this.gameobject:computePathfinding(this.transform:getPosition(), input.mouse.worldPosition, true, 32.0);
	end
end