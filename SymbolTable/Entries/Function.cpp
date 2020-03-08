//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Function.h"

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

