damage = 20; -- -public -int
tagTarget = "NULL"; -- -public -string

function OnPhysicCollision(_collider)
	if (_collider.tag == tagTarget) then
		lifeScript = _collider:getScript("life");
		if (lifeScript ~= nil) then
			lifeScript:setInt("life", lifeScript:getInt("life") - damage);
		end
		this.gameobject:destroy();
	end
end