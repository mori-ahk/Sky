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
        SymbolTable() = default;

        ~SymbolTable() = default;

        void addClass(std::string &, Class *);

        void addFunction(std::string &, Function *);

        Function *getFreeFunction(std::string &, Function *);

        Class *getClass(std::string &);

        std::unordered_map<std::string, Class *> classes;
        std::unordered_map<std::string, std::vector<Function *> > freeFunctions;
        Function *main = new Function(Visibility::PUBLIC, "main", "void", {}, {}, 0);
    };
}

#endif //SKY_SYMBOLTABLE_H
