damage = 125; -- -public -int
enemyTag = "player"; -- -public -string

myLifeScript = 0;

function OnStart()
	myLifeScript = this.gameobject:getScript("life");
end

function OnPhysicCollision(_collider)
	if (_collider.tag == "player") then
		currentEnemy = _collider;
		currentEnemyLifeScript = currentEnemy:getScript("life");
		if (currentEnemyLifeScript ~= nil) then
			currentEnemyLife = currentEnemyLifeScript:getInt("life");
			currentEnemyLife = currentEnemyLife - damage;
			currentEnemyLifeScript:setInt("life", currentEnemyLife);
		end
		if (myLifeScript ~= nil) then
			myLifeScript:setInt("life", 0);
		end
	end
end