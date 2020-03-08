//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_CLASS_H
#define SKY_CLASS_H

#include <string>
#include <unordered_map>
#include "Function.h"
#include "Variable.h"
class Class {
public:

    const std::string &getName() const;

    const std::string &getType() const;

    const std::unordered_map<std::string, Function *> &getFunctions() const;

    const std::unordered_map<std::string, Variable *> &getVariables() const;

private:
    std::string name;
    std::string type;
    std::unordered_map<std::string, Function*> functions;
    std::unordered_map<std::string, Variable*> variables;

};


#endif //SKY_CLASS_H
