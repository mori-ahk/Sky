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
    for(auto dim: v.getDimensions()) dimension += std::to_string(dim) + ", ";
    os << "[" <<  "visibility: " << "private" << "| name: " << v.getName() << " | type: "  << v.getType() <<  "| dimensions: " << dimension << "]" << std::endl;
    return os;
}