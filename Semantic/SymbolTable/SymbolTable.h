//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_SYMBOLTABLE_H
#define SKY_SYMBOLTABLE_H

#include "Entries/Class.h"
#include "Entries/Function.h"
#include "../Error/Error.h"
#include <unordered_map>
#include <vector>


namespace Semantic {
    class SymbolTable {
    public:
        SymbolTable();
        ~SymbolTable();

        void addClass(std::string&, Class*);
        void addFunction(std::string&, Function*);
        void addError(std::pair<std::string, int>&);

        Class* getClass(std::string&);
        bool doesMatch(Function&, Function&);
        std::unordered_map<std::string, Class *> classes;
        std::unordered_map<std::string, std::vector<Function *> > freeFunctions;
        Function *main = new Function(Visibility::PUBLIC, "main", "void", {}, {});

        std::vector<std::pair<std::string, int>> errors;
    };
}

#endif //SKY_SYMBOLTABLE_H