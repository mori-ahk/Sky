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
    if (freeFunctions.find(funcName) != freeFunctions.end()) {
        int tag = freeFunctions.at(funcName).size();
        function->setTag(funcName + "_" + std::to_string(tag));
        freeFunctions.at(funcName).push_back(function);
    } else {
        function->setTag(funcName + "_" + std::to_string(0));
        freeFunctions[funcName].push_back(function);
    }
}

Function* Semantic::SymbolTable::getFreeFunction(const std::string &funcName, Function *function) const {
    if (freeFunctions.find(funcName) == freeFunctions.end())
        throw Semantic::Err::UndeclaredFunction(funcName, function->getPosition());
    for (auto &f : freeFunctions.at(funcName)) {
        if (*f == *function) return f;
    }
    throw Semantic::Err::UndeclaredFunction(funcName, function->getPosition());
}

const std::vector<Function *> &Semantic::SymbolTable::getFreeFunction(const std::string &funcName) const {
    if (freeFunctions.find(funcName) == freeFunctions.end())
        throw Semantic::Err::UndeclaredFunction(funcName, 0);

    return freeFunctions.at(funcName);
}

Class *Semantic::SymbolTable::getClass(const std::string &className) {
    if (classes.find(className) == classes.end())
        throw Semantic::Err::UndeclaredClass(className);

    return classes.at(className);
}