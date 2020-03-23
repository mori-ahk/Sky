//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "SymbolTable.h"
#include "../Error/Error.h"

void Semantic::SymbolTable::addClass(std::string &className, Class *_class) {
    if (classes.find(className) != classes.end())
        throw Semantic::Err::DuplicateClassDecl(className);

    classes[className] = _class;
}

void Semantic::SymbolTable::addFunction(std::string &funcName, Function *function) {
    freeFunctions[funcName].push_back(function);
}

Function* Semantic::SymbolTable::getFreeFunction(std::string &funcName, Function *function) {
    if (freeFunctions.find(funcName) == freeFunctions.end())
        throw Semantic::Err::UndeclaredFunction(funcName, function->getPosition());
    for (auto &f : freeFunctions.at(funcName)) {
        if (*f == *function) return f;
    }
    throw Semantic::Err::UndeclaredFunction(funcName, function->getPosition());
}

std::vector<Function *> Semantic::SymbolTable::getFreeFunction(std::string &funcName) {
    if (freeFunctions.find(funcName) == freeFunctions.end())
        throw Semantic::Err::UndeclaredFunction(funcName, 0);

    return freeFunctions[funcName];
}

Class *Semantic::SymbolTable::getClass(std::string &className) {
    if (classes.find(className) == classes.end())
        throw Semantic::Err::UndeclaredClass(className);

    return classes.at(className);
}