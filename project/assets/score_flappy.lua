function OnPhysicCollisionEnter(_collider)
	if(string.find(_collider.name, "flappy") ~= nil) then
		debug.log("SCORE !");
		SoundBuffer:playSound();
	end
end