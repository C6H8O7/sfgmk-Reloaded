AvailableRessource = 50; -- -public -int

InitialAvailableRessource = 0;


function OnStart()

	InitialAvailableRessource = AvailableRessource;

end

function OnUpdate()
	
	--Scale en fonction des ressources restantes
	Scale = AvailableRessource / InitialAvailableRessource;
	this.transform:setScale( r_vector2f(Scale, Scale));
	
end