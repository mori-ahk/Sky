//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_FUNCTION_H
#define SKY_FUNCTION_H



#include <vector>
#include "Variable.h"
#include "Visibility.h"

class Function {
public:

    Function(Visibility visibility, std::string name, std::string returnType, std::vector<Variable*> params);
    std::vector<Variable*>& getParams();
    std::string& getName();
    std::string& getReturnType();
    Visibility getVisibility();
private:

    std::vector<Variable*> params;
    std::string name;
    std::string returnType;
    Visibility visibility;
};


#endif //SKY_FUNCTION_H
