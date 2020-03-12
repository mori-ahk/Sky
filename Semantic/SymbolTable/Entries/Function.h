//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_FUNCTION_H
#define SKY_FUNCTION_H



#include <vector>
#include "Variable.h"
#include "Visibility.h"
#include <iostream>
class Function {
public:

    Function(Visibility visibility, std::string name, std::string returnType, std::vector<Variable*> params, std::vector<Variable*> localVars);
    std::vector<Variable*>& getParams();
    std::vector<Variable*>& getLocalVars();
    std::string& getName();
    std::string& getReturnType();
    std::string getVisibilityString();
    Visibility getVisibility();

    void addParam(Variable*);
    void addVariable(Variable*);
    static bool isParamsEqual(Function&, Function&);
    friend std::ostream& operator<<(std::ostream&, Function&);
    bool isDefined;

    friend inline bool operator==(Function& lhs, Function& rhs)  {
        return lhs.getName() == rhs.getName() &&
               isParamsEqual(lhs,rhs) &&
               lhs.getVisibilityString() == rhs.getVisibilityString() &&
               lhs.getReturnType() == rhs.getReturnType();
    }
private:

    std::vector<Variable*> params;
    std::vector<Variable*> localVars;
    std::string name;
    std::string returnType;
    Visibility visibility;
};


#endif //SKY_FUNCTION_H
