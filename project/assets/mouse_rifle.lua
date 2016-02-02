function OnUpdate()
	if(input.mouse.left == 3) then
		bullet = game.instantiate("bullet");
		bullet.transform.position.x = input.mouse.worldPosition.x;
		bullet.transform.position.y = input.mouse.worldPosition.y;
	end
end