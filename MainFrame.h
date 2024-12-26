#pragma once
#include <wx/wx.h>
#include <wx/filedlg.h>
#include <fstream>
#include <sstream>

class MainFrame : public wxFrame {

public:
	MainFrame(const wxString& title);
private:

	//Sizer
	wxBoxSizer* mainSizer;
	wxBoxSizer* leftSizer;
	wxBoxSizer* middleSizer;
	wxBoxSizer* rightSizer;
	//Buttons
	wxButton* openBtn;
	wxButton* assembleBtn;
	wxButton* saveBtn;
	//img
	wxBitmap bitmap;

	//txtBox
	wxTextCtrl* iTextBox; //text box za asm
	wxTextCtrl* oTextBox;//text box za machine code
	wxTextCtrl* symTextBox; //za loop adrese

	void openFile(wxCommandEvent& event);
	void assemble(wxCommandEvent& event);
	void saveFile(wxCommandEvent& event);
};