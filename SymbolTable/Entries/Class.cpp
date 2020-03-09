//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Class.h"

Class::Class(std::string name, std::string type, std::string inherits) {
    this->name = name;
    this->type = type;
    this->inherits = inherits;
}

std::string &Class::getName() {
    return name;
}

std::string &Class::getType() {
    return type;
}

std::string& Class::getInherits() {
    return inherits;
}

std::unordered_map<std::string, Function *> &Class::getFunctions() {
    return functions;
}

std::unordered_map<std::string, Variable *> &Class::getVariables() {
    return variables;
}


void Class::addVariable(std::string& varName, Variable* variable) {
    variables[varName] = variable;
}