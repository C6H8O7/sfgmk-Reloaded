speed = 100.0; -- -public -float
limitPercent = 10.0; -- -public -float
LimitX = 0.0;
LimitY = 0.0;
screenSizeX = 1280.0; -- -public -float
screenSizeY = 720.0; -- -public -float


function OnStart()

	LimitX = screenSizeX * (limitPercent / 100.0);
	LimitY = screenSizeY * (limitPercent / 100.0);

end

function OnUpdate()
	
	CurrentPos = this.transform:getPosition();
	MousePosition = input.mouse.unscaledWindowPosition;

	--Contraint la position souris à la fenêtre
	if MousePosition.x < 0.0 then
		MousePosition.x = 0.0;
	elseif MousePosition.x > screenSizeX then
		MousePosition.x = screenSizeX;
	end

	if MousePosition.y < 0.0 then
		MousePosition.y = 0.0;
	elseif MousePosition.y > screenSizeY then
		MousePosition.y = screenSizeY;
	end
	
	--Check si on est sur un bord d'écran, et déplace la caméra en fonction de la proximité de ce bord
	if MousePosition.x <= LimitX  then
		FinalSpeed = speed * (LimitX -  MousePosition.x) / LimitX;
		CurrentPos.x = CurrentPos.x - FinalSpeed * time.deltaTime;
	elseif MousePosition.x >= screenSizeX - LimitX  then
		FinalSpeed = speed * ((MousePosition.x - (screenSizeX - LimitX)) / LimitX);
		CurrentPos.x = CurrentPos.x + FinalSpeed * time.deltaTime;
	end

	if MousePosition.y <= LimitY  then
		FinalSpeed = speed * (LimitY -  MousePosition.y) / LimitY;
		CurrentPos.y = CurrentPos.y - FinalSpeed * time.deltaTime;
	elseif MousePosition.y >= screenSizeY - LimitY  then
		FinalSpeed = speed * ((MousePosition.y - (screenSizeY - LimitY)) / LimitY);
		CurrentPos.y = CurrentPos.y + FinalSpeed * time.deltaTime;
	end

	this.transform:setPosition(CurrentPos);
	
end