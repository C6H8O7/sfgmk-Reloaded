gameobjectName = "NULL"; -- -public -string
scriptName = "NULL"; -- -public -string
intName = "NULL"; -- -public -string;

script = nil;
valid = 0;

function getGameObject()
	if (valid == 0) then
		gameobject = game.getGameObjectByName(gameobjectName);
		
		if (gameobject ~= nil) then
			script = gameobject:getScript(scriptName);
			
			if (script ~= nil) then
				valid = 1;
			end
		end
	end
end

function OnUpdate()
	getGameObject();
	if (valid == 1) then
		this.gameobject.text = tostring(script:getInt(intName));
	end
end