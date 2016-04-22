money = 1000; -- -public -int
cooldownMoney = 10.0; -- -public -float
automoneyAmount = 25; -- -public -int
triangleAmount = 50; -- -public -int

timer = 0.0;

function OnUpdate()
	timer = timer + time.deltaTime;
	
	if (timer >= cooldownMoney) then
		timer = 0.0;
		money = money + automoneyAmount;
	end
end

function triangleProc()
	money = money + triangleAmount;
end