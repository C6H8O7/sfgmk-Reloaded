Ressource = 50;
RessourceText = 0;


function OnStart()

	RessourceText = game.getGameObjectByName("RessourceText");

end

function OnUpdate()
	
	RessourceText.text = string.format("%s %i", "Ressource:", Ressource);
	
end