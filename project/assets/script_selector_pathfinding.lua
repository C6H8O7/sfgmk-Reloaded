function OnUpdate()
	if this.debug.selected == true then
		if input.mouse.right == 1 then
			this.pathfinding:computePathfinding(this.transform.position, input.mouse.worldPosition, true, 32.0);
		end
	end
end