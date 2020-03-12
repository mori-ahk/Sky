//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Class.h"
#include "../../Error/Error.h"

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

std::unordered_map<std::string, std::vector<Function *> > &Class::getFunctions() {
    return functions;
}

std::unordered_map<std::string, Variable *> &Class::getVariables() {
    return variables;
}

Function* Class::getFunction(std::string& funcName) {
    if (functions.find(funcName) == functions.end())
        throw Semantic::Err::UndeclaredFunction(funcName);
    return functions.at(funcName).size() < 2 ? functions.at(funcName).at(0) : functions.at(funcName).at(1);
}

void Class::addVariable(std::string& varName, Variable* variable) {
    if (variables.find(varName) != variables.end())
        throw Semantic::Err::DuplicateDataMember();

    variables[varName] = variable;
}

void Class::addFunction(std::string& funcName, Function* function) {
    functions[funcName].push_back(function);
}

std::ostream& operator<<(std::ostream& os, Class& c) {
    os << "CLASS:\n";
    os << "[ " <<  "name: " << c.getName() << " | inherits: " << c.getInherits() << " | type: "  << c.getType() << " ]" << std::endl;
    for(auto f : c.getFunctions()) {
        for (auto& _f : f.second)
            os << "\t" << *(_f) << std::endl;
    }

    for(auto v: c.getVariables()) {
        os << "\t" << *(v.second) << std::endl;
    }

    return os;
}