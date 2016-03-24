function OnUpdate()
	debug.log("mouse_debug");
	mouse_position = input.mouse.unscaledWindowPosition;
	debug.log(tostring(mouse_position.x));
end