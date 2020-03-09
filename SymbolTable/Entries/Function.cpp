//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Function.h"

Function::Function(Visibility visibility, std::string name, std::string returnType, std::vector<Variable *> params) {
    this->visibility = visibility;
    this->name = name;
    this->returnType = returnType;
    this->params = params;
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

Visibility Function::getVisibility() {
    return visibility;
}

