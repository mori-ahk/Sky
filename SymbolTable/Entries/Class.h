//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_CLASS_H
#define SKY_CLASS_H


#include "Symbol.h"

class Class: public Symbol {
public:
    Class(std::string name, SymbolKind kind, SymbolTable* table)
    : Symbol(name, SymbolKind::CLASS, table) {}
    ~Class();
private:

};


#endif //SKY_CLASS_H
