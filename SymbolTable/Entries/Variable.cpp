//
// Created by Morteza Ahmadi on 2020-03-05.
//

#include "Variable.h"

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