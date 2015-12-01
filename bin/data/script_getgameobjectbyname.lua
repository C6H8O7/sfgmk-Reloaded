goomba1 = game.getGameObjectByName("g1");

function OnUpdate()
	if goomba1 then
		goomba1.transform.position.x = goomba1.transform.position.x + 10 * time.deltaTime;
		if goomba1.transform.position.x > 1000 then
			game.removeGameObject(goomba1);
			game.removeGameObject(game.getGameObjectByName("script"));
			goomba1 = nil;
		end
	end
end