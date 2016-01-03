function OnUpdate()
	if input.mouse.right == 1 then
		this.pathfinding:computePathfinding(this.transform.position, input.mouse.worldPosition, false, 0.0);
	end
end