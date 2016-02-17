uiBasicFormationNumber = 0; -- -public -int

function OnStart()
	-- Instatiate Base
	for i = 1, uiBasicFormationNumber, 1
		do
		  Entity = game.instantiate("BasicFormation");
		  Entity.transform:setPosition(r_vector2f(math.random(0.0, 1280.0), math.random(0.0, 720.0)));
		end
	for i = 1, uiBasicFormationNumber, 1
		do
		  Entity = game.instantiate("BasicFormation2");
		  Entity.transform:setPosition(r_vector2f(math.random(0.0, 1280.0), math.random(0.0, 720.0)));
		end
	for i = 1, uiBasicFormationNumber, 1
		do
		  Entity = game.instantiate("BasicFormation3");
		  Entity.transform:setPosition(r_vector2f(math.random(0.0, 1280.0), math.random(0.0, 720.0)));
		end
end