peonCreationTime = 5.0; -- -public -float
peonCost = 50; -- -public -int

timer = peonCreationTime;
RessourceManager = 0;
RessourceManagerScript = 0;
IsCreatingPeon = false;
Position = 0;


function OnStart()

	RessourceManager = game.getGameObjectByName("RessourceManager");
	RessourceManagerScript = RessourceManager:getScript("w_RessourceManager");
	Position = this.transform:getPosition();

end

function OnUpdate()

	--En attente des ressources pour créer un péon
	if IsCreatingPeon == false then
		currentRessource = RessourceManagerScript:getInt("Ressource");

		if currentRessource >= peonCost then
			currentRessource = currentRessource - peonCost;
			RessourceManagerScript:setInt("Ressource", currentRessource);
			IsCreatingPeon = true;
		end

	--En train de créer un péon
	else
		timer = timer - time.deltaTime;

		if timer <= 0.0 then
			timer = peonCreationTime;
			IsCreatingPeon = false;
			Entity = game.instantiate("Peon");
			PeonPosition = Position + r_vector2f(32.0, 32.0);
			Entity.transform:setPosition(PeonPosition);
		end

		debug.log("Peon creation: ");
		debug.log(timer);
	end
end