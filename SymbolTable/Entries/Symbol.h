//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_SYMBOL_H
#define SKY_SYMBOL_H

#include <string>
#include "SymbolKind.h"
#include "../SymbolTable.h"

class Symbol {
public:
    Symbol();
    Symbol(std::string, SymbolKind, SymbolTable*);
    ~Symbol();

    std::string& getName();
    SymbolKind getKind();
    SymbolTable* getTable();

private:

    std::string name;
    SymbolKind kind;
    SymbolTable* table;

};


#endif //SKY_SYMBOL_H
