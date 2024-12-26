#include "Parser.h"
#include <bitset>

Parser::Parser() {

	compDict.clear();
	destDict.clear();
	jumpDict.clear();

	compEntry("0","0101010");
    compEntry("1", "0111111");
    compEntry("-1", "0111010");
    compEntry("D", "0001100");
    compEntry("A", "0110000");
    compEntry("!D", "0001101");
    compEntry("!A", "0110001");
    compEntry("-D", "0001111");
    compEntry("-A", "0110011");
    compEntry("D+1", "0011111");
    compEntry("1+D", "0011111");  
    compEntry("A+1", "0110111");
    compEntry("1+A", "0110111");  
    compEntry("D-1", "0001110");
    compEntry("A-1", "0110010");
    compEntry("D+A", "0000010");
    compEntry("A+D", "0000010");  
    compEntry("D-A", "0010011");
    compEntry("A-D", "0000111");
    compEntry("D&A", "0000000");
    compEntry("A&D", "0000000");  
    compEntry("D|A", "0010101");
    compEntry("A|D", "0010101");

    compEntry("M", "1110000");
    compEntry("!M", "1110001");
    compEntry("-M", "1110011");
    compEntry("M+1", "1110111");
    compEntry("1+M", "1110111");
    compEntry("M-1", "1110010");
    compEntry("D+M", "1000010");
    compEntry("M+D", "1000010"); 
    compEntry("D-M", "1010011");
    compEntry("M-D", "1000111");
    compEntry("D&M", "1000000");
    compEntry("M&D", "1000000");  
    compEntry("D|M", "1010101");
    compEntry("M|D", "1010101");  

    destEntry("null", "000");
    destEntry("M", "001");
    destEntry("D", "010");
    destEntry("MD", "011");
    destEntry("DM", "011");  
    destEntry("A", "100");
    destEntry("AM", "101");
    destEntry("MA", "101");  
    destEntry("AD", "110");
    destEntry("DA", "110");   
    destEntry("AMD", "111");  
    destEntry("ADM", "111");
    destEntry("MAD", "111");
    destEntry("MDA", "111");
    destEntry("DAM", "111");
    destEntry("DMA", "111");

    jumpEntry("null", "000");
    jumpEntry("JGT", "001");
    jumpEntry("JEQ", "010");
    jumpEntry("JGE", "011");
    jumpEntry("JLT", "100");
    jumpEntry("JNE", "101");
    jumpEntry("JLE", "110");
    jumpEntry("JMP", "111");
}

Parser::~Parser(){}

void Parser::compEntry(std::string key, std::string val) {
	compDict.insert(std::pair<std::string, std::string>(key, val));
}
void Parser::destEntry(std::string key, std::string val) {
	destDict.insert(std::pair<std::string, std::string>(key, val));
}
void Parser::jumpEntry(std::string key, std::string val) {
	jumpDict.insert(std::pair<std::string, std::string>(key, val));
}

std::string Parser::compLookup(std::string instComp) {

    if (compDict.find(instComp) != compDict.end()) {
        return compDict.find(instComp)->second;
    }
    else
        throw std::runtime_error("non-existen function");
}
std::string Parser::destLookup(std::string instDest) {

    if (instDest == "null")
        return destDict.find("null")->second;
    else if (destDict.find(instDest) != destDict.end())
        return destDict.find(instDest)->second;
    else
        throw std::runtime_error("non-existen destination");
}
std::string Parser::jumpLookup(std::string instJump) {

    if (instJump == "null") {
        return jumpDict.find("null")->second;
    }
    else if (jumpDict.find(instJump) != jumpDict.end())
        return jumpDict.find(instJump)->second;
    else
        throw std::runtime_error("non-existen jump");
}

std::string Parser::parseInst(std::string inst) {
    std::string tempInst;
    
    if (inst.find('@') != std::string::npos) {
        tempInst = inst.substr(1);  // brisanje '@'
        return parseAInst(tempInst); // prosledjujemo A-inst
    }
    else {
        return parseCInst(inst);
    }
}

std::string Parser::parseAInst(std::string inst){

    if (inst.find_first_not_of("0123456789")==std::string::npos) { //ako su samo brojevi
        return prefixA + std::bitset<15>(stoi(inst)).to_string();
    }
    else {
        if (inst.find_first_of("0123456789") < inst.find_first_not_of("0123456789")) {  //ako idu brojevi pa slova
            throw std::runtime_error("Parser::parseAInst(): invalid A-instruction");
        }
        else {                                                  //ako idu slova pa brojevi
            auto addr = SyTb.lookupSymbolTable(inst);           //proveravamo da li je predifinisano, ako nije dodajemo u table
            return prefixA + std::bitset<15>(addr).to_string();
        }
    }
}

std::string Parser::parseCInst(std::string inst) {

    std::string::size_type ideq = inst.find('=');                  // za velicinu stringa se koristi ili za rad sa indeksima u stringu size_type
    std::string::size_type idsc = inst.find(';');                 //cuvamo indeks gde se nalaze karakteri

    std::string instDest = (ideq != std::string::npos) ? inst.substr(0, ideq) : "null";
    std::string instComp = inst.substr(ideq + 1, idsc - ideq - 1);
    std::string instJump = (idsc != std::string::npos) ? inst.substr(idsc + 1): "null";

    return prefixC + compLookup(instComp) + destLookup(instDest) + jumpLookup(instJump);
}