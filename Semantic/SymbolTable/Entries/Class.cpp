//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Class.h"

#include <utility>
#include "../../Error/Error.h"

Class::Class(std::string name, std::string type, std::vector<std::string> inherits) {
    this->name = std::move(name);
    this->type = std::move(type);
    this->inherits = std::move(inherits);
}

std::string &Class::getName() {
    return name;
}

std::string &Class::getType() {
    return type;
}

std::vector<std::string>& Class::getInherits() {
    return inherits;
}

std::unordered_map<std::string, std::vector<Function *> > &Class::getFunctions() {
    return functions;
}

std::unordered_map<std::string, Variable *> &Class::getVariables() {
    return variables;
}

Function* Class::getFunction(std::string& funcName, Function* function) {
    if (functions.find(funcName) == functions.end())
        throw Semantic::Err::UndeclaredFunction(funcName);
    for (auto& f : functions[funcName]) {
        if ( *f == *function) return f;
    }
    throw Semantic::Err::UndeclaredFunction(funcName);
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
    std::string inherits;
    for (auto& s : c.getInherits()) {
        inherits += s + ",";
    }
    if (!inherits.empty()) inherits.pop_back();
    os << "CLASS:\n";
    os << "[ " <<  "name: " << c.getName() << " | inherits: " << inherits << " | type: "  << c.getType() << " ]" << std::endl;
    for(auto& f : c.getFunctions()) {
        for (auto& _f : f.second)
            os << "\t" << *(_f) << std::endl;
    }

    for(auto& v: c.getVariables()) {
        os << "\t" << *(v.second) << std::endl;
    }

    return os;
}