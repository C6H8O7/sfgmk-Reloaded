speed = 100.0; -- -public -float
width = 1280.0; -- -public -float
nx = 1280.0; -- -public -float

function OnUpdate()
	this.transform.position.x = this.transform.position.x - speed * time.deltaTime;
	
	if this.transform.position.x <= -width then
		this.transform.position.x = nx;
	end
end