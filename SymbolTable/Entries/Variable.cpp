//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Variable.h"

Variable::Variable(Visibility visibility, std::string name, std::string type, std::vector<int> dimensions) {
    this->visibility = visibility;
    this->name = name;
    this->type = type;
    this->dimensions = std::move(dimensions);
}

std::vector<int>& Variable::getDimensions() {
    return dimensions;
}

std::string& Variable::getType() {
    return type;
}

std::string& Variable::getName() {
    return name;
}

Visibility Variable::getVisibility() {
    return visibility;
}

std::ostream& operator<<(std::ostream& os, Variable& v) {
    std::string dimension = "";
    std::string visibility;
    if (v.getVisibility() == Visibility::PUBLIC) visibility = "public";
    else visibility = "private";
    os << "VARIABLE\n";
    for(auto dim: v.getDimensions()) dimension += std::to_string(dim) + ", ";
    if (v.getDimensions().empty() or v.getDimensions().at(0) == -1) dimension = "[]";
    os << "\t[ " <<  "visibility: " << visibility << " | name: " << v.getName() << " | type: "  << v.getType() <<  " | dimensions: " << dimension << " ]" << std::endl;
    return os;
}