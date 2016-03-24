Ressource = 50; -- -public -int
ressourceText = 0;


function OnStart()

	ressourceText = this.gameobject;

end

function OnUpdate()
	
	ressourceText.text = string.format("%s %i", "Ressource:", Ressource);

end