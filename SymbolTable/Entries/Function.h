//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_FUNCTION_H
#define SKY_FUNCTION_H



#include <vector>
#include "Variable.h"
#include "SymbolKind.h"

class Function {
public:

    Function(std::string name, SymbolKind kind, std::string typeName);
    std::vector<Variable*>& getParams();
private:
    std::vector<Variable*> params;
};


#endif //SKY_FUNCTION_H
