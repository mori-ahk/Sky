//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Variable.h"

#include <utility>

Variable::Variable(Visibility visibility, std::string name, std::string type, int dimensions, int position) {
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

std::string &Variable::getName() {
    return name;
}

std::string Variable::getVisibilityString() {
    if (getVisibility() == Visibility::PUBLIC) return "public";
    else return "private";
}

Visibility Variable::getVisibility() {
    return visibility;
}

std::ostream &operator<<(std::ostream &os, Variable &v) {
    std::string dimension = std::to_string(v.getDimensions());
    std::string visibility = v.getVisibilityString();
    os << "[ " << "visibility: " << visibility << " | name: " << v.getName() << " | type: " << v.getType()
       << " | dimensions: " << dimension << " ]" << std::endl;
    return os;
}
