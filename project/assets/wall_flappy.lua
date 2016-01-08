speed = 150.0;

function OnUpdate()
	this.transform.position.x = this.transform.position.x - speed * time.deltaTime;
	
	offsetX = 0.0;
	if this.transform.rotation > 0.0 then
		offsetX = 78.0;
	end
	
	if this.transform.position.x < (0.0 + offsetX - 78.0) then
		this.transform.position.x = 1280.0 + offsetX + 78.0;
	end
end