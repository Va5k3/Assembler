#include "SymbolTable.h"


SymbolTable SyTb;

SymbolTable::SymbolTable() {

	table.clear();

	table.insert(std::pair<std::string, uint16_t>("SP", 0));
	table.insert(std::pair<std::string,uint16_t>("LCL", 1));
	table.insert(std::pair<std::string,uint16_t>("ARG", 2));
	table.insert(std::pair<std::string,uint16_t>("THIS", 3));
	table.insert(std::pair<std::string, uint16_t>("THAT", 4));

	//VIRTUALNI REGISTRI

	table.insert(std::pair<std::string,uint16_t>("R0",0));
	table.insert(std::pair<std::string,uint16_t>("R1",1));
	table.insert(std::pair<std::string,uint16_t>("R2",2));
	table.insert(std::pair<std::string,uint16_t>("R3",3));
	table.insert(std::pair<std::string,uint16_t>("R4",4));
	table.insert(std::pair<std::string,uint16_t>("R5",5));
	table.insert(std::pair<std::string,uint16_t>("R6",6));
	table.insert(std::pair<std::string,uint16_t>("R7",7));
	table.insert(std::pair<std::string,uint16_t>("R8",8));
	table.insert(std::pair<std::string,uint16_t>("R9",9));
	table.insert(std::pair<std::string,uint16_t>("R10",10));
	table.insert(std::pair<std::string,uint16_t>("R11",11));
	table.insert(std::pair<std::string,uint16_t>("R12",12));
	table.insert(std::pair<std::string,uint16_t>("R13",13));
	table.insert(std::pair<std::string,uint16_t>("R14",14));
	table.insert(std::pair<std::string, uint16_t>("R15", 15));

	table.insert(std::pair<std::string,uint16_t>("SCREEN", 16384));
	table.insert(std::pair<std::string,uint16_t>("KBD", 24576));

	VarCounter = 16;
	LblCounter = 0;

}

SymbolTable::~SymbolTable() { table.clear();}
int SymbolTable::incLblCounter() { return LblCounter++; }

void SymbolTable::addLabel(std::string Label) {
	if (table.find(Label) != table.end()) 
		throw std::runtime_error("addLabel(): redifened label.");
	else {
		table.insert(std::pair<std::string, uint16_t>(Label, LblCounter));
		std::cerr << "Label is added" << '\n';
	}
}

void SymbolTable::addVar(std::string Var) {
	if (table.find(Var) == table.end())
	table.insert(std::pair<std::string, uint16_t>(Var, VarCounter));
	VarCounter++;
}

uint16_t SymbolTable::lookupSymbolTable(std::string Var) { 
	addVar(Var);
	return table.find(Var)->second;
}


