#include "MainFrame.h"
#include "Assembler.h"
#include <wx/wx.h>


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title,wxDefaultPosition, wxSize(1000,600)) {

	wxPanel* panel = new wxPanel(this, wxID_ANY); //platno za crtanje


	//Sizeri
	mainSizer = new wxBoxSizer(wxHORIZONTAL);
	leftSizer = new wxBoxSizer(wxVERTICAL);
	middleSizer = new wxBoxSizer(wxVERTICAL);
	rightSizer = new wxBoxSizer(wxVERTICAL);
	//dugmici
	openBtn = new wxButton(panel, wxID_OPEN, "Open File", wxDefaultPosition,wxSize(100,35));
	assembleBtn = new wxButton(panel, wxID_EXECUTE, "Assemble");
	saveBtn = new wxButton(panel, wxID_SAVE, "Save output");
	//txtBox
	iTextBox = new wxTextCtrl(panel, wxID_ANY, "Upload a file or manually write the assembly code.", wxDefaultPosition, wxSize(380, 150), wxTE_MULTILINE);
	oTextBox = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(380, 150), wxTE_MULTILINE | wxTE_READONLY);
	symTextBox = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(150, 150), wxTE_MULTILINE | wxTE_READONLY);
	//dodavanje el u sizer
	leftSizer->Add(openBtn, 0, wxALL, 5);
	leftSizer->Add(0, 0, 1, wxEXPAND); //razmak
	leftSizer->Add(symTextBox, 0, wxALL, 5);
	middleSizer->Add(iTextBox, 1, wxEXPAND | wxALL, 5);
	middleSizer->Add(assembleBtn, 0, wxEXPAND | wxALL, 5);
	rightSizer->Add(oTextBox, 1, wxEXPAND | wxALL, 5);
	rightSizer->Add(saveBtn, 0, wxEXPAND | wxALL, 5);
	mainSizer->Add(leftSizer, 0, wxEXPAND | wxALL, 5);
	mainSizer->Add(middleSizer, 0, wxEXPAND | wxALL, 5);
	mainSizer->Add(rightSizer, 0, wxEXPAND | wxALL, 5);
	//setovanje sizera u panel
	panel->SetSizer(mainSizer);

	//mesto za bindings
	Bind(wxEVT_BUTTON, &MainFrame::openFile, this, wxID_OPEN);
	Bind(wxEVT_BUTTON, &MainFrame::saveFile, this, wxID_SAVE);
	Bind(wxEVT_BUTTON, &MainFrame::assemble, this, wxID_EXECUTE);


}

void MainFrame::openFile(wxCommandEvent& event) {

	wxFileDialog openForeignFile(this, "Open Assembly File", "", "", "Assembly Files (*.asm) | *.asm", wxFD_OPEN | wxFD_FILE_MUST_EXIST); //klasa za rad sa fajlovima

	if (openForeignFile.ShowModal() == wxID_CANCEL) return; //showModal blokira dalju interakciju dok korisnik ne pretisne cancle ili izadje iz tog prozora

	std::ifstream file(openForeignFile.GetPath().ToStdString()); //ifstream otvara fajl koji vraca putanju fajla gde se nalazi i pretvara u string

	if (!file.is_open()) {
		wxMessageBox("Could not open the file.","Error",wxICON_ERROR);
		return;
	}

	std::ostringstream buffer;
	buffer << file.rdbuf();
	iTextBox->SetValue(buffer.str());
}
void MainFrame::saveFile(wxCommandEvent& event) {
	
	wxFileDialog saveForeignFile(this, "Save Machine Code","","", "Machine Code Files (*.hack) | *.hack", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveForeignFile.ShowModal() == wxID_CANCEL) return;

	std::ofstream file(saveForeignFile.GetPath().ToStdString());
	if (!file.is_open()) {
		wxMessageBox("Could not save file.", "Error", wxICON_ERROR);
		return;
	}
	file << oTextBox->GetValue().ToStdString();
	wxMessageBox("File save successfully", "Info", wxICON_INFORMATION);
}

void MainFrame::assemble(wxCommandEvent& event) {

	wxString input = iTextBox->GetValue();

	if (input.IsEmpty()) {
		wxMessageBox("Input text is empty. Please load an assembly", "Error", wxICON_ERROR);
		return;
	}

	std::string tempInputFile = "temp.asm";
	std::ofstream tempInFile(tempInputFile);
	tempInFile << input.ToStdString();
	tempInFile.close();

	std::string tempOutPutFile = "output.hack";
	std::string tempOutPutFile2 = "SymbolTable.txt";  //DODATO 11:01

	try {
	
		Assembler assembler;
		assembler.assemble(tempInputFile, tempOutPutFile, tempOutPutFile2);						 //DODATO 11:01
		std::ifstream outFile(tempOutPutFile);
		std::ifstream outFile2(tempOutPutFile2);
		if (!outFile.is_open())
			throw std::runtime_error("Unable to open output file");

		std::ostringstream buffer;
		buffer << outFile.rdbuf();
		oTextBox->SetValue(buffer.str());

		if (!outFile.is_open())
			throw std::runtime_error("Unable to open output file");
		std::ostringstream buffer2;
		buffer2 << outFile2.rdbuf();
		symTextBox->SetValue(buffer2.str());

	}catch(const std::exception& e) {
		wxMessageBox(e.what(), "Error", wxICON_ERROR);
	}



}

