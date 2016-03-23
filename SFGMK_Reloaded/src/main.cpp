#include "stdafx.h"

#ifdef SFGMKR_EDITOR

class MainApp : public wxApp
{
public:
	virtual r_bool OnInit()
	{
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);

		MyGUI *win = new MyGUI(0);

		MyGUI::SetGUI(win);

		SFMLCanvas::gameCanvas = win->GUI_PreviewSFML;
		SFMLCanvas::editorCanvas = win->GUI_EditorSFML;

		win->Show(TRUE);
		return TRUE;
	}
};

IMPLEMENT_APP(MainApp)

#endif

#ifndef SFGMKR_EDITOR
#ifndef SFGMKR_ANDROID

#include <Windows.h>

r_int32 WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, r_int32 nCmdShow)
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	r_string projectPath = "..\\..\\project\\project.gmkproject";

	printf("SFGMK Reloaded starting...\n");
	printf("Loading %s project file...\n", projectPath.c_str());

	SFMLCanvas* canvas = new SFMLCanvas();

	SFMLCanvas::gameCanvas = canvas;

	SFMLCanvas::project = new Project();
	SFMLCanvas::project->load(projectPath);

	SFMLCanvas::gameCanvas->isPlaying = true;

	while( canvas->window.isOpen() )
		canvas->OnUpdate();

	gmk::Factory::getSingleton()->releaseSingleton();

	return 0;
}

#endif
#endif

#ifdef SFGMKR_ANDROID

int main(int argc, char *argv[])
{
	gmk::Debug::Log(r_string("[INFO] Starting SFGMKR !!"));
	
	r_string projectPath = "project.gmkproject";

	SFMLCanvas* canvas = new SFMLCanvas();

	SFMLCanvas::gameCanvas = canvas;

	SFMLCanvas::project = new Project();
	SFMLCanvas::project->load(projectPath);

	SFMLCanvas::isPlaying = true;

	while (canvas->window.isOpen())
		canvas->OnUpdate();

	gmk::Factory::getSingleton()->releaseSingleton();

	return 0;
}

#endif