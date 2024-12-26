#include "App.h"
#include "MainFrame.h"



bool App::OnInit() { //postavljanje glavnog prozora

	MainFrame* mainFrame = new MainFrame("V45k3 - Assembler");
	mainFrame->Show();
	return true;

}

wxIMPLEMENT_APP(App);
