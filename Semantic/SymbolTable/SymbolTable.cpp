//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "SymbolTable.h"
#include "../Error/SemanticError.h"

Semantic::SymbolTable::SymbolTable() {}

void Semantic::SymbolTable::addClass(std::string &className, Class * _class) {
    if (classes.find(className) != classes.end())
        throw Semantic::Error(Type::MULTDECCLASS);

    classes[className] = _class;
}