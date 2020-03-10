//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_SYMBOLTABLE_H
#define SKY_SYMBOLTABLE_H

#include "Entries/Class.h"
#include "Entries/Function.h"
#include <unordered_map>

namespace Semantic {
    class SymbolTable {
    public:
        SymbolTable();

        ~SymbolTable();

        std::unordered_map<std::string, Class *> classes;
        std::unordered_map<std::string, Function *> freeFunctions;
        Function *main = new Function(Visibility::PUBLIC, "main", "void", {}, {});
    };
}

#endif //SKY_SYMBOLTABLE_H
