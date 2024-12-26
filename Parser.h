#pragma once
#include "SymbolTable.h"
#include <cstdint>
#include <map>
#include <stdexcept>
#include <string>

extern SymbolTable SyTb;

class Parser {

	//table za C instrukciju
	std::map<std::string,std::string> compDict;
	std::map<std::string,std::string> destDict;
	std::map<std::string,std::string> jumpDict;

	std::string prefixA = "0";
	std::string prefixC = "111";

	//ubacivanje u table
	void compEntry(std::string key, std::string val);
	void destEntry(std::string key, std::string val);
	void jumpEntry(std::string key, std::string val);

	//vracaju machine code za C delove
	std::string compLookup(std::string instComp); 
	std::string jumpLookup(std::string instJump);
	std::string destLookup(std::string instDest);
	
	std::string parseAInst(std::string inst);
	std::string parseCInst(std::string inst);


public:
	Parser();
	~Parser();
	std::string parseInst(std::string inst);









};