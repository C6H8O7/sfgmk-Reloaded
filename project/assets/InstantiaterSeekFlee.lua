uiSeekerNumber = 0; -- -public -int
uiFleeerNumber = 0; -- -public -int


function OnStart()
	-- Instatiate Seekers
	for i = 1, uiSeekerNumber, 1
		do
		  Entity = game.instantiate("Seeker");
		  Entity.rigidbody:setPosition(gmk.Vector2f(math.random(0.0, 1280.0), math.random(0.0, 720.0)));
		end

	-- Instatiate Fleeers
	for i = 1, uiFleeerNumber, 1
		do
		  Entity = game.instantiate("Fleeer");
		  Entity.rigidbody:setPosition(gmk.Vector2f(math.random(0.0, 1280.0), math.random(0.0, 720.0)));
		end
end