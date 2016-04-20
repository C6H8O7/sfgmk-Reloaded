function OnPhysicCollisionEnter(_collider)
	if (_collider.tag == "enemy") then
		debug.log(_collider.name);
		debug.log("game over");
	end
end