//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Class.h"

std::string &Class::getName() {
    return name;
}

std::string &Class::getType() {
    return type;
}

std::unordered_map<std::string, Function *> &Class::getFunctions() {
    return functions;
}

std::unordered_map<std::string, Variable *> &Class::getVariables() {
    return variables;
}
