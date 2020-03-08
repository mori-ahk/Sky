//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_VARIABLE_H
#define SKY_VARIABLE_H


#include "Symbol.h"
#include <vector>

class Variable : public Symbol {
public:

    Variable(std::string name, SymbolKind kind, std::string type, std::vector<int> dimensions)
    : Symbol(name, SymbolKind::VARIABLE, nullptr) {
        this->type = type;
        this->dimensions = std::move(dimensions);
    }

    std::string& getType();
    std::vector<int>& getDimensions();

private:

    std::string type;
    std::vector<int> dimensions;
};


#endif //SKY_VARIABLE_H
