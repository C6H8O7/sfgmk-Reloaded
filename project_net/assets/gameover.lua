function OnPhysicCollisionEnter(_collider)
	if (_collider.tag == "enemy") then
		doGameOver();
		net.sendGameObjectCall("gameoverzone", "gameover", "doGameOver");
	end
end

function doGameOver()
	net.clean();
	game.loadScene("Menu");
end