//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "SymbolTable.h"
#include "../Error/Error.h"

void Semantic::SymbolTable::addClass(std::string& className, Class* _class) {
    if (classes.find(className) != classes.end())
        throw Semantic::Err::DuplicateClassDecl();

    classes[className] = _class;
}

void Semantic::SymbolTable::addFunction(std::string& funcName, Function* function) {
    freeFunctions[funcName].push_back(function);
}

void Semantic::SymbolTable::buildDependencyGraph() {
    for (auto& _class : classes) {
        auto node = new DependencyNode(_class.first);
        for (std::string& inherit : _class.second->getInherits()) {
            try { getClass(inherit); }
            catch (Semantic::Err::UndeclaredClass &undeclaredClass) { throw; }
            node->addToList(inherit);
        }
        for (auto& _variable : _class.second->getVariables()) {
            std::string localVarType = _variable.second->getType();
            if (classes.find(localVarType) != classes.end()) node->addToList(localVarType);
        }
        dependencyGraph->nodes.push_back(node);
    }
}

Class* Semantic::SymbolTable::getClass(std::string& className) {
    if (classes.find(className) == classes.end())
        throw Semantic::Err::UndeclaredClass(className);

    return classes.at(className);
}