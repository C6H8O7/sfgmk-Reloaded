Distance = 2048.0; -- -public -float
RecoltTime = 5.0; -- -public -float
RecoltAccount = 10.0; -- -public -float

HotelDeVille = 0;
Mine = 0;
Target = 0;
bIsRecolting = false;
bHasMoney = false;
timer = 0.0;

RessourceScript = 0;
CityRessourceScript = 0;


function OnStart()

	HotelDeVille = game.getGameObjectByName("HotelDeVille");
	Mine = game.getGameObjectByName("Money");	
	Target = Mine;

	RessourceScript = Mine:getScript("w_Ressource");
	CityRessourceScript = game.getGameObjectByName("RessourceManager"):getScript("w_RessourceManager");
	 
end

function OnUpdate()

	--En train de récolter
	if bIsRecolting then
		timer = timer + time.deltaTime;
		if timer >= RecoltTime then
			bIsRecolting = false;
			bHasMoney = true;
			timer = 0.0;
			this.steering:setWeight("SteeringArrival", 1.0);

			currentRessource = RessourceScript:getInt("AvailableRessource");
			currentRessource = currentRessource - RecoltAccount;
			RessourceScript:setInt("AvailableRessource", currentRessource);
		end

	--En chemin
	else
		VecX = this.transform:getPosition().x - Target.transform:getPosition().x;
		VecY = this.transform:getPosition().y - Target.transform:getPosition().y;
		Dist =  VecX*VecX + VecY*VecY;

		if Dist < Distance then
			if bHasMoney then
				bHasMoney = false;
				Target = Mine;
				this.steering:setTarget("SteeringArrival", Mine);

				currentRessource = CityRessourceScript:getInt("Ressource");
				currentRessource = currentRessource + RecoltAccount;
				CityRessourceScript:setInt("Ressource", currentRessource);
			else
				currentRessource = RessourceScript:getInt("AvailableRessource");	
				if currentRessource >= RecoltAccount then
					bIsRecolting = true;
					Target = HotelDeVille;
					this.steering:setTarget("SteeringArrival", HotelDeVille);
				end

				this.steering:setWeight("SteeringArrival", 0.0);
				this.rigidbody:cleanForces();
				this.rigidbody:cleanSpeed();
			end
		end
	end
end