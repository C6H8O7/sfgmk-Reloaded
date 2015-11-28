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

		win->Show(TRUE);

		SetTopWindow(win);

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

	printf("SFGMK Reloaded starting...\n");

	Scene::Load("../data/scene.xml");

	SFMLCanvas* canvas = new SFMLCanvas();

	const int fps_range = 1000;

	while (canvas->isOpen())
	{
		canvas->OnUpdate();

		static sf::Clock clock;
		static int i = 0;
		static float f = 0.0f;

		f += clock.restart().asSeconds();

		if (i++ > fps_range)
		{
			printf("FPS: %f\n", 1.0f / (f / fps_range));
			i = 0;
			f = 0.0f;
		}
	}

	return 0;
}

#endif