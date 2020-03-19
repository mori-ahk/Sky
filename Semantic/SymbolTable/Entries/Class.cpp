//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Class.h"

#include <utility>
#include "../../Error/Error.h"

Class::Class(std::string name, std::string type, std::vector<std::string> inherits, int position) {
    this->name = std::move(name);
    this->type = std::move(type);
    this->inherits = std::move(inherits);
    this->position = position;
}

std::string &Class::getName() {
    return name;
}

std::string &Class::getType() {
    return type;
}

std::vector<std::string> &Class::getInherits() {
    return inherits;
}

std::unordered_map<std::string, std::vector<Function *> > &Class::getFunctions() {
    return functions;
}

std::unordered_map<std::string, Variable *> &Class::getVariables() {
    return variables;
}

Function *Class::getFunction(std::string &funcName, Function *function) {
    if (functions.find(funcName) == functions.end())
        throw Semantic::Err::UndeclaredFunction(funcName, function->getPosition());
    for (auto &f : functions[funcName]) {
        if (*f == *function) return f;
    }
    throw Semantic::Err::UndeclaredFunction(funcName, function->getPosition());
}

Variable *Class::getVariable(std::string &varName) {
    if (variables.find(varName) == variables.end())
        throw Semantic::Err::UndeclaredClassVariable(varName);
    return variables.at(varName);
}

void Class::addVariable(std::string &varName, Variable *variable) {
    if (variables.find(varName) != variables.end())
        throw Semantic::Err::DuplicateDataMember(varName, variable->getPosition());

    variables[varName] = variable;
}

void Class::addFunction(std::string &funcName, Function *function) {
    functions[funcName].push_back(function);
}

std::vector<std::string> Class::findShadowMembers(Class &_class1) {
    std::vector<std::string> shadowMessages;
    for (const auto &v1: _class1.getVariables()) {
        if (getVariables().find(v1.first) != getVariables().end()) {
            auto v2 = getVariables().at(v1.first);
            if (*v1.second == *v2) {
                std::string shadowMessage =
                        "Shadow variable " + v1.first + " between " + _class1.getName() + " and " + getName();
                shadowMessages.push_back(shadowMessage);
            }
        }
    }

    for (const auto &c1: _class1.getFunctions()) {
        for (const auto &f1 : c1.second) {
            if (getFunctions().find(c1.first) != getFunctions().end()) {
                for (const auto &f2 : getFunctions().at(c1.first)) {
                    if (*f1 == *f2) {
                        std::string shadowMessage =
                                "Shadow function " + f1->getName() + " between " + _class1.getName() + " and " +
                                getName();
                        shadowMessages.push_back(shadowMessage);
                    }
                }
            }
        }
    }

    return shadowMessages;
}


std::ostream &operator<<(std::ostream &os, Class &c) {

    std::string inherits;
    for (auto &s : c.getInherits()) {
        inherits += s + ",";
    }
    if (!inherits.empty()) inherits.pop_back();
    os << "CLASS:\n";
    os << "[ " << "name: " << c.getName() << " | inherits: " << inherits << " | type: " << c.getType() << " ]"
       << std::endl;
    for (auto &f : c.getFunctions()) {
        for (auto &_f : f.second)
            os << "\t" << *(_f) << std::endl;
    }

    for (auto &v: c.getVariables()) {
        os << "\t" << *(v.second) << std::endl;
    }

    return os;
}