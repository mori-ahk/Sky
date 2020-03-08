//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_CLASSDECL_H
#define SKY_CLASS_H

#include <string>
#include <unordered_map>
#include "Function.h"
#include "Variable.h"
class ClassDecl {
public:

    std::string &getName();
    std::string &getType();
    std::unordered_map<std::string, Function *> &getFunctions();
    std::unordered_map<std::string, Variable *> &getVariables();

private:
    std::string name;
    std::string type;
    std::unordered_map<std::string, Function*> functions;
    std::unordered_map<std::string, Variable*> variables;

};


#endif //SKY_CLASSDECL_H
