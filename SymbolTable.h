#pragma once
#include <cstdint>
#include <map>
#include <stdexcept>
#include <string>
#include <iostream>


class SymbolTable {



public:
	int VarCounter;  //broji adresu varijable
	int LblCounter; //broji adresu labele
	std::map<std::string, uint16_t> table; //symbolTable
	SymbolTable(); 
	~SymbolTable();
	int incLblCounter();
	void addLabel(std::string Label); //dodavanje labele u table
	void addVar(std::string Var); //dodavanje var u table
	uint16_t lookupSymbolTable(std::string Var); //vraca nam adresu varijable ili je dodaje ako je nema


};