//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_SYMBOLTABLE_H
#define SKY_SYMBOLTABLE_H

#include "Entries/Class.h"
#include "Entries/Function.h"
#include <unordered_map>

class SymbolTable {
public:
    static std::unordered_map<std::string, ClassDecl*> classes;
    static std::unordered_map<std::string, Function*> freeFunctions;
    static std::unordered_map<std::string, Function*> main;
};


#endif //SKY_SYMBOLTABLE_H
