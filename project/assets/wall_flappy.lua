speed = 150.0;

function OnUpdate()
	this.transform.position.x = this.transform.position.x - speed * time.deltaTime;
	
	if this.transform.position.x < -78.0 then
		this.transform.position.x = 1280.0;
	end
end