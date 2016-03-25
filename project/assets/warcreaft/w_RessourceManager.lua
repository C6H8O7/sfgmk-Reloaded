Ressource = 50; -- -public -int
ScreenSizeX = 1280.0; -- -public -float
ScreenSizeY = 720.0; -- -public -float

ressourceText = 0;
Camera = 0;


function OnStart()

	ressourceText = this.gameobject;
	Camera = game.getGameObjectByName("MainCamera");

	ScreenSizeX = ScreenSizeX * 0.5;
	ScreenSizeY = ScreenSizeY * 0.5;

end

function OnUpdate()
	
	--Position Hud fixe
	Position = Camera.transform:getPosition();
	Position.x = Position.x - ScreenSizeX;
	Position.y = Position.y - ScreenSizeY;
	this.transform:setPosition(Position);

	--Affichage ressources dispos
	ressourceText.text = string.format("%s %i", "Ressource:", Ressource);

end