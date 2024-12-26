#include "Assembler.h"

Assembler::Assembler() {}
Assembler::~Assembler() {}

void Assembler::assemble(const std::string& inputFile, const std::string& outputFile, const std::string& outputFile2) {		//DODATO 11:01

	std::ifstream fIn(inputFile);
	if (!fIn.is_open())
		throw std::runtime_error("Unable to open file " + inputFile);
	std::ofstream fOut(outputFile);
	if (!fOut.is_open())
		throw std::runtime_error("Unable to open file " + outputFile);
	std::ofstream fOut2(outputFile2);													//DODATO 11:01
	if (!fOut2.is_open())
		throw std::runtime_error("Unable to open file " + outputFile2);
	std::queue<std::string>queue1, queue2;

	asmEdit(fIn, queue1);  //ucitavanje assemblera u queue (brisanje space, komentara)
	firstPass(queue1, queue2); //brisanje labela iz reda
	secondPass(queue2, fOut);  //pisanje u outfile
	tableWrite(fOut2);															//DODATO 11:01
}
void Assembler::asmEdit(std::ifstream& fIn, std::queue<std::string>&queue1) {
	std::string line;
	while (getline(fIn, line)) {
		std::string::size_type idx = line.find("//");
		std::string lineRmComm = line.substr(0, idx);	//cuvanje stringova do '//'

		if (lineRmComm.size() == 0) continue;  //idi na sledeci line
		//brisanje space
		std::string::iterator str_iter = remove(lineRmComm.begin(), lineRmComm.end(), ' ');  //stavlja space sve na kraj i vraca iterator
	
		lineRmComm.erase(str_iter, lineRmComm.end());
		queue1.push(lineRmComm);  //pushamo string bez komentara i bez space
	}
}
void Assembler::firstPass(std::queue<std::string>& queue1, std::queue<std::string>& queue2) {
	std::string line;

	while (!queue1.empty()) {
		line = queue1.front();
		queue1.pop();

		if (line.find('(') != std::string::npos && line.find(')') != std::string::npos) {
			std::string::size_type idx_l = line.find_last_of('(');
			std::string::size_type idx_r = line.find_first_of(')');
			line = line.substr(idx_l + 1, idx_r - idx_l - 1);

			SyTb.addLabel(line);
			symTable.insert(std::pair<std::string, int>(line, SyTb.LblCounter));	// DODATO
			continue;
		}
		else {
			SyTb.incLblCounter();
		}
		queue2.push(line);  //pusovanje bez labela
	}
}
void Assembler::secondPass(std::queue<std::string>& queue2, std::ofstream& fOut) {
	std::string line;
	while (!queue2.empty()) {
		line = queue2.front();
		queue2.pop();
		std::string macCode = Prs.parseInst(line);
		fOut << macCode<<'\n';
		
	}
}
void Assembler::tableWrite(std::ofstream& fOut2) {			//DODATO 11:01
	for (auto& [key, value] : symTable) {
		fOut2 << key << " : " << value << '\n';
	}
}



