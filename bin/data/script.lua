function OnUpdate()
	this.transform.rotation = this.transform.rotation + 360.0 * time.deltaTime;
	
	debug.log(this.transform.rotation);
end