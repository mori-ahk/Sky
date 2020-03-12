//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Function.h"
#include "../../Error/Error.h"

Function::Function(Visibility visibility, std::string name, std::string returnType, std::vector<Variable *> params, std::vector<Variable*> localVars) {
    this->visibility = visibility;
    this->name = name;
    this->returnType = returnType;
    this->params = params;
    this->localVars = localVars;
    this->isDefined = false;
}

std::string& Function::getName() {
    return name;
}

std::string& Function::getReturnType() {
    return returnType;
}

std::string Function::getVisibilityString() {
    if (getVisibility() == Visibility::PUBLIC) return "public";
    else return "private";
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
    for (auto param : params)
        if (param->getName() == variable->getName())
            throw Semantic::Err::DuplicateFuncParam();

    params.push_back(variable);
    addVariable(variable);
}

void Function::addVariable(Variable* variable) {
    for (auto var: localVars)
        if (var->getName() == variable->getName())
            throw Semantic::Err::DuplicateDataMember();

    localVars.push_back(variable);
}

std::ostream& operator<<(std::ostream& os, Function& f) {
    std::string visibility = f.getVisibilityString();
    os << "FUNCTION:\n";
    os << "\t[ " <<  "visibility: " << visibility << " | name: " << f.getName() << " | returns: "  << f.getReturnType() << " ]" << std::endl;
    for (auto& var : f.getLocalVars()) {
        os << "\t\t" << *var << std::endl;
    }
    return os;
}

bool Function::isParamsEqual(Function &lhs, Function &rhs) {
    if (lhs.getParams().size() != rhs.getParams().size()) return false;
    for (int i = 0; i < lhs.getParams().size(); i++) {
        auto lParam = *lhs.getParams().at(i);
        auto rParam = *rhs.getParams().at(i);
        if (lParam == rParam) continue;
        else return false;
    }

    return true;
}
