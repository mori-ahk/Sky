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

Visibility Function::getVisibility() {
    return visibility;
}

void Function::addParam(Variable * variable) {
    params.push_back(variable);
}

void Function::addVariable(Variable* variable) {
    localVars.push_back(variable);
}

std::ostream& operator<<(std::ostream& os, Function& f) {
    std::string visibility;
    if (f.getVisibility() == Visibility::PUBLIC) visibility = "public";
    else visibility = "private";
    os << "FUNCTION:\n";
    os << "\t[" <<  "visibility: " << visibility << "| name: " << f.getName() << " | returns: "  << f.getReturnType() << "]" << std::endl;
    os << "\t\tParams:\n";
    for (auto& var : f.getParams()) {
        std::string dimension = "";
        for(auto dim: var->getDimensions()) dimension += std::to_string(dim) + " ";
        os << "\t\t[" <<  "visibility: " << "private" << "| name: " << var->getName() << " | type: "  << var->getType() <<  "| dimensions: " << dimension << "]" << std::endl;
    }
    return os;
}
