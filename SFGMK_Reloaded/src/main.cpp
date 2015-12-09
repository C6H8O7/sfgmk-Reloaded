#ifdef SFGMKR_EDITOR

class MainApp : public wxApp
{

public:

	virtual bool OnInit()
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	std::string projectPath = "../../project/project.gmkproject";

	printf("SFGMK Reloaded starting...\n");
	printf("Loading %s project file...\n", projectPath.c_str());

	SFMLCanvas* canvas = new SFMLCanvas();

	SFMLCanvas::gameCanvas = canvas;

	SFMLCanvas::project = new Project();
	SFMLCanvas::project->load(projectPath);

	while( canvas->isOpen() )
		canvas->OnUpdate();

	return 0;
}

#endif