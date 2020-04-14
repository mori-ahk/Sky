//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Function.h"

#include <utility>
#include "../../Error/Error.h"

Function::Function(Enums::Visibility visibility, std::string name, std::string returnType, std::vector<Variable *> params,
                   std::vector<Variable *> localVars, int position) {
    this->visibility = visibility;
    this->name = std::move(name);
    this->returnType = std::move(returnType);
    this->params = std::move(params);
    this->localVars = std::move(localVars);
    this->position = position;
    this->isDefined = false;
    this->offset = 0;
    this->size = 0;
}

const std::string &Function::getName() const {
    return name;
}

const std::string &Function::getReturnType() const {
    return returnType;
}

std::string Function::getVisibilityString() const {
    if (getVisibility() == Enums::Visibility::PUBLIC) return "public";
    else return "private";
}

const std::vector<Variable *> &Function::getParams() const {
    return params;
}

const std::vector<Variable *> &Function::getLocalVars() const {
    return localVars;
}

Variable *Function::getVariable(std::string &varName) const {
    for (const auto& var : localVars) {
        if (var->getName() == varName) return var;
    }
    throw Semantic::Err::UndeclaredLocalVariable(varName);
}

Enums::Visibility Function::getVisibility() const {
    return visibility;
}

void Function::addParam(Variable *variable) {
    for (auto param : params)
        if (param->getName() == variable->getName())
            throw Semantic::Err::DuplicateFuncParam(variable->getPosition());

    params.push_back(variable);
    addVariable(variable);
}

void Function::addVariable(Variable *variable) {
    for (auto var: localVars)
        if (var->getName() == variable->getName())
            throw Semantic::Err::DuplicateDataMember(variable->getName(), variable->getPosition());

    localVars.push_back(variable);
}

std::ostream &operator<<(std::ostream &os, Function &f) {
    std::string visibility = f.getVisibilityString();
    os << "FUNCTION:\n";
    os << "\t[ " << "visibility: " << visibility << " | name: " << f.getName() << " | returns: " << f.getReturnType()
       << " ]" << std::endl;
    os << "\t\tVARIABLE(S): \n";
    for (auto &var : f.getLocalVars()) {
        os << "\t\t" << *var;
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

int Function::getOffset() const {
    return offset;
}

void Function::setOffset(int _offset) {
    Function::offset = _offset;
}

int Function::getSize() const {
    return size;
}

void Function::setSize(int size) {
    Function::size = size;
}

int Function::getVariableOffset() const {
    if (sizes.size() == 1) return 0;
    int toReturn = 0;
    for (int i = 0; i < sizes.size() - 1; i++) toReturn += sizes.at(i);
    return toReturn;
}

const std::string &Function::getTag() const {
    return tag;
}

void Function::setTag(const std::string &tag) {
    Function::tag = tag;
}
