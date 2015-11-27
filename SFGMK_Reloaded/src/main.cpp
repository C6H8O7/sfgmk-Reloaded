class MainApp : public wxApp
{

public:

	virtual bool OnInit()
	{
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);

		MyGUI *MainWin = new MyGUI(0);
		MainWin->Show(TRUE);
		SetTopWindow(MainWin);

		return TRUE;
	}
};

IMPLEMENT_APP(MainApp)