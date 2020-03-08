//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Class.h"

std::string &ClassDecl::getName() {
    return name;
}

std::string &ClassDecl::getType() {
    return type;
}

std::unordered_map<std::string, Function *> &ClassDecl::getFunctions() {
    return functions;
}

std::unordered_map<std::string, Variable *> &ClassDecl::getVariables() {
    return variables;
}
