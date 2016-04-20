damage = 10; -- -public -int
cooldown = 2.0; -- -public -float
enemyTag = "player"; -- -public -string

currentEnemy = nil;
lastEnemy = nil;
currentEnemyLifeScript = nil;
translationScript = nil;

timer = 0.0;

function OnStart()
	translationScript = this.gameobject:getScript("translation");
end

function OnUpdate()
	if (currentEnemy ~= nil) then
		timer = timer + time.deltaTime;
		if (timer >= cooldown) then
			timer = 0.0;
			currentEnemyLifeScript:setInt("life", currentEnemyLifeScript:getInt("life") - damage);
		end
	end
end

function OnPhysicEnter()
	currentEnemy = nil;
end

function OnPhysicCollision(_collider)
	if (_collider.tag == "player") then
		currentEnemy = _collider;
		if (lastEnemy == nil) then
			lastEnemy = currentEnemy;
			currentEnemyLifeScript = currentEnemy:getScript("life");
			if (translationScript ~= nil) then
				translationScript:setInt("enabled", 0);
			end
		end
	end
end

function OnPhysicExit()
	if (currentEnemy == nil and lastEnemy ~= nil) then
		lastEnemy = nil;
		if (translationScript ~= nil) then
			translationScript:setInt("enabled", 1);
		end
	end
end