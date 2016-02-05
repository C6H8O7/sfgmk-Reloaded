goomba1 = game.getGameObjectByName("g1");

function OnUpdate()
	if goomba1 then
		currentPos = goomba1.transform:getPosition();
		currentPos.x = currentPos + 10 * time.deltaTime;
		goomba1.transform:setPosition(currentPos);
		if currentPos.x > 1000 then
			game.removeGameObject(goomba1);
			game.removeGameObject(this.gameobject);
			goomba1 = nil;
		end
	end
end