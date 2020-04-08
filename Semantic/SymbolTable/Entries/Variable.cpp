//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Variable.h"

#include <utility>

Variable::Variable(Enums::Enums visibility, std::string name, std::string type, int dimensions, int position) {
    this->visibility = visibility;
    this->name = std::move(name);
    this->type = std::move(type);
    this->dimensions = dimensions;
    this->position = position;
}

int &Variable::getDimensions() {
    return dimensions;
}

std::string &Variable::getType() {
    return type;
}

std::string Variable::getRawType() {
    std::string rawType;
    for (auto c : getType()) {
        if (c != '[' && c != ']') rawType += c;
        else break;
    }
    return rawType;
}

std::string &Variable::getName() {
    return name;
}

std::string Variable::getVisibilityString() {
    if (getVisibility() == Enums::Enums::PUBLIC) return "public";
    else return "private";
}

Enums::Enums Variable::getVisibility() {
    return visibility;
}

std::ostream &operator<<(std::ostream &os, Variable &v) {
    std::string dimension = std::to_string(v.getDimensions());
    std::string visibility = v.getVisibilityString();
    os << "[ " << "visibility: " << visibility << " | name: " << v.getName() << " | type: " << v.getType()
       << " | dimensions: " << dimension << " ]" << std::endl;
    return os;
}
