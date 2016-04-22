damage = 125; -- -public -int
enemyTag = "player"; -- -public -string

function OnPhysicCollision(_collider)
	if (_collider.tag == "player") then
		currentEnemy = _collider;
		currentEnemyLifeScript = currentEnemy:getScript("life");
		if (currentEnemyLifeScript ~= nil) then
			currentEnemyLife = currentEnemyLifeScript:getInt("life");
			currentEnemyLife = currentEnemyLife - damage;
			currentEnemyLifeScript:setInt("life", currentEnemyLife);
		end
		this.gameobject:destroy();
	end
end