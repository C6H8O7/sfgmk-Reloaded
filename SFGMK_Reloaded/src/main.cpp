

class MainApp : public wxApp // MainApp is the class for our application
{
	// MainApp just acts as a container for the window,
public: // or frame in MainFrame
	virtual bool OnInit()
	{
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);

		// Create an instance of our frame, or window
		MyGUI *MainWin = new MyGUI(0);

		MainWin->Show(TRUE);

		SetTopWindow(MainWin);

		return TRUE;
	}
};

IMPLEMENT_APP(MainApp)