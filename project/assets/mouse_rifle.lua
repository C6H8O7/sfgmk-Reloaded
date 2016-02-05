function OnUpdate()
	if(input.mouse.left == 3) then
		bullet = game.instantiate("bullet");
		bullet.transform:setPosition(input.mouse.worldPosition);
	end
end