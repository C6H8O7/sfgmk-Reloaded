#include "stdafx.h"

#ifdef SFGMKR_EDITOR

class wxWorkspaceFrame : public wxFrame
{
public:
	wxWorkspaceFrame(wxFrame *parent, wxWindowID id = wxID_ANY,
		const wxString& title = _T("wxWorkspaceView Sample"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE | wxCLIP_CHILDREN | wxNO_FULL_REPAINT_ON_RESIZE)
		: wxFrame(parent, id, title, pos, size, style)
	{
		//WorkspaceView::ThijzWorkspaceFactory* Factory = new WorkspaceView::ThijzWorkspaceFactory();
		WorkspaceView::BasicWorkspaceFactory* Factory = new WorkspaceView::BasicWorkspaceFactory();

		Workspace = new wxWorkspaceView(Factory, this);
		//Workspace->SetWatermark(wxT("Watermark.jpg"), WatermarkPositionBottomRight);
		//Workspace->SetBackColor(wxColor(0, 0, 0));
		//Workspace->SetGridColor(wxColor(60, 60, 60));
		Workspace->SetAntiAlias(true);

		WorkspaceView::Node* Item1 = Factory->CreateNode(wxRect(100, 100, 100, 100), 2, 4, wxT("This is Sample Node 1"));
		WorkspaceView::Node* Item2 = Factory->CreateNode(wxRect(300, 300, 100, 100), 2, 2, wxT("Sample Node 2"));
		WorkspaceView::Cable* Item3 = Factory->CreateCable(Item1, Item2, 0, 0);

		Item1->Select();

		Workspace->AddItem(Item1);
		Workspace->AddItem(Item2);
		Workspace->AddItem(Item3);
	}
private:
	wxWorkspaceView *Workspace;
};

class MainApp : public wxApp
{

public:

	/*virtual r_bool OnInit()
	{
		wxWorkspaceFrame *Frame = new wxWorkspaceFrame(
			NULL, wxID_ANY, wxT("wxWorkspaceView Sample"),
			wxDefaultPosition, wxSize(640, 480));
		Frame->Show(true);

		return true;
	}*/

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

	r_string projectPath = "../../project/project.gmkproject";

	printf("SFGMK Reloaded starting...\n");
	printf("Loading %s project file...\n", projectPath.c_str());

	SFMLCanvas* canvas = new SFMLCanvas();

	SFMLCanvas::gameCanvas = canvas;

	SFMLCanvas::project = new Project();
	SFMLCanvas::project->load(projectPath);

	SFMLCanvas::isPlaying = true;

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