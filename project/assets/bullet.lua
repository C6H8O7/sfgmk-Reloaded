speed = 200.0;

function OnUpdate()
	currentPos = this.transform:getPosition();
	currentPos.x = currentPos.x + speed * time.deltaTime;
	this.transform:setPosition(currentPos);
	if(this.transform:getPosition().x > 1280.0) then
		this.gameobject:destroy();
	end
end