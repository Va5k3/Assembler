#pragma once
#include <iostream>
#include "SymbolTable.h"
#include "Parser.h"
#include <fstream> 
#include <algorithm> //sort, search, copy, remove element
#include <queue>

class Assembler{

private:
	SymbolTable SyTb;
	Parser Prs;
	std::map<std::string, int> symTable;
	void asmEdit(std::ifstream& fIn, std::queue<std::string>& queue1);;
	void firstPass(std::queue<std::string>&queue1, std::queue<std::string>&queue2);
	void secondPass(std::queue<std::string>& queue2, std::ofstream& fOut);
	void tableWrite(std::ofstream& fOut2);														//DODATO 11:01

public:
	Assembler();
	~Assembler();
	
	void assemble(const std::string& inputFile, const std::string& outputFile, const std::string& outputFile2);		//DODATO 11:01

};