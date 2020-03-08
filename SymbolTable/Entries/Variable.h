//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_VARIABLE_H
#define SKY_VARIABLE_H

#include <string>
#include <vector>
#include "SymbolKind.h"
#include "Visibility.h"

class Variable {
public:

    Variable(std::string name, SymbolKind kind, std::string type, std::vector<int> dimensions) {
        this->type = type;
        this->dimensions = std::move(dimensions);
    }

    std::string& getType();
    std::vector<int>& getDimensions();
    std::string& getName();
    Visibility getVisibility();
private:

    std::string type;
    std::string name;
    std::vector<int> dimensions;
    Visibility visibility;
};


#endif //SKY_VARIABLE_H