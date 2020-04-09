//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Variable.h"

Variable::Variable(Enums::Visibility visibility, std::string name, std::string type, int dimensions, int position) {
    this->visibility = visibility;
    this->name = std::move(name);
    this->type = std::move(type);
    this->dimensions = dimensions;
    this->position = position;
}

const int &Variable::getDimensions() const {
    return dimensions;
}

const std::string &Variable::getType() const {
    return type;
}

std::string Variable::getRawType() const {
    std::string rawType;
    for (auto c : getType()) {
        if (c != '[' && c != ']') rawType += c;
        else break;
    }
    return rawType;
}

const std::string &Variable::getName() const {
    return name;
}

std::string Variable::getVisibilityString() const {
    if (getVisibility() == Enums::Visibility::PUBLIC) return "public";
    else return "private";
}

Enums::Visibility Variable::getVisibility() const {
    return visibility;
}

std::ostream &operator<<(std::ostream &os, Variable &v) {
    std::string dimension = std::to_string(v.getDimensions());
    std::string visibility = v.getVisibilityString();
    os << "[ " << "visibility: " << visibility << " | name: " << v.getName() << " | type: " << v.getType()
       << " | dimensions: " << dimension << " ]" << std::endl;
    return os;
}

Enums::Kind Variable::getKind() const {
    return kind;
}
