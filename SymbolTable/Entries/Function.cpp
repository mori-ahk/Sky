//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Function.h"

Function::Function(Visibility visibility, std::string name, std::string returnType, std::vector<Variable *> params, std::vector<Variable*> localVars) {
    this->visibility = visibility;
    this->name = name;
    this->returnType = returnType;
    this->params = params;
    this->localVars = localVars;
}

std::string& Function::getName() {
    return name;
}

std::string& Function::getReturnType() {
    return returnType;
}

std::vector<Variable *> & Function::getParams() {
    return params;
}

std::vector<Variable *>& Function::getLocalVars() {
    return localVars;
}

Visibility Function::getVisibility() {
    return visibility;
}

void Function::addParam(Variable * variable) {
    params.push_back(variable);
    localVars.push_back(variable);
}

void Function::addVariable(Variable* variable) {
    localVars.push_back(variable);
}



std::ostream& operator<<(std::ostream& os, Function& f) {
    std::string visibility;
    if (f.getVisibility() == Visibility::PUBLIC) visibility = "public";
    else visibility = "private";
    os << "FUNCTION:\n";
    os << "\t[ " <<  "visibility: " << visibility << " | name: " << f.getName() << " | returns: "  << f.getReturnType() << " ]" << std::endl;
    for (auto& var : f.getLocalVars()) {
        os << "\t\t" << *var << std::endl;
    }
    return os;
}
