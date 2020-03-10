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

void Class::addFunction(std::string& funcName, Function* function) {
    functions[funcName] = function;
}

std::ostream& operator<<(std::ostream& os, Class& c) {
    os << "CLASS:\n";
    os << "[ " <<  "name: " << c.getName() << " | inherits: " << c.getInherits() << " | type: "  << c.getType() << " ]" << std::endl;
    for(auto f : c.getFunctions()) {
        os << "\t" << *(f.second) << std::endl;
    }

    for(auto v: c.getVariables()) {
        os << "\t" << *(v.second) << std::endl;
    }

    return os;
}