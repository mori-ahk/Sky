//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Class.h"

const std::string &Class::getName() const {
    return name;
}

const std::string &Class::getType() const {
    return type;
}

const std::unordered_map<std::string, Function *> &Class::getFunctions() const {
    return functions;
}

const std::unordered_map<std::string, Variable *> &Class::getVariables() const {
    return variables;
}
