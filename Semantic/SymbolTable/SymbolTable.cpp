//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "SymbolTable.h"
#include "../Error/Error.h"


Semantic::SymbolTable::SymbolTable() {}


void Semantic::SymbolTable::addClass(std::string &className, Class * _class) {
    if (classes.find(className) != classes.end())
        throw Semantic::Err::DuplicateClassDecl();

    classes[className] = _class;
}

void Semantic::SymbolTable::addError(std::pair<const char*, int> & error) {
        errors.push_back(error);
}

Class* Semantic::SymbolTable::getClass(std::string& className) {
    if (classes.find(className) == classes.end())
        throw Semantic::Err::UndeclaredClass(className);

    return classes.at(className);
}