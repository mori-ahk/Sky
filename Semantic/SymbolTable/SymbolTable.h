//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_SYMBOLTABLE_H
#define SKY_SYMBOLTABLE_H

#include "Entries/Class.h"
#include "Entries/Function.h"
#include "../Error/Error.h"
#include "DependencyGraph.h"
#include <unordered_map>
#include <vector>


namespace Semantic {
    class SymbolTable {
    public:
        SymbolTable() = default;
        ~SymbolTable() = default;

        void addClass(std::string&, Class*);
        void addFunction(std::string&, Function*);
        void buildDependencyGraph();

        Class* getClass(std::string&);
        std::unordered_map<std::string, Class *> classes;
        std::unordered_map<std::string, std::vector<Function *> > freeFunctions;
        Function *main = new Function(Visibility::PUBLIC, "main", "void", {}, {});
        DependencyGraph* dependencyGraph = new DependencyGraph();
    };
}

#endif //SKY_SYMBOLTABLE_H
