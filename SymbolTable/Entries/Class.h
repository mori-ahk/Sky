//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_CLASS_H
#define SKY_CLASS_H

#include <string>
#include <unordered_map>
#include "Function.h"
#include "Variable.h"
#include <iostream>
class Class {
public:

    Class(std::string, std::string, std::string);
    ~Class();
    std::string &getName();
    std::string &getType();
    std::string& getInherits();
    std::unordered_map<std::string, Function *> &getFunctions();
    std::unordered_map<std::string, Variable *> &getVariables();

    void addVariable(std::string&, Variable*);
    void addFunction(std::string&, Function*);
    friend std::ostream& operator<<(std::ostream&, Class&);

private:
    std::string name;
    std::string type;
    std::string inherits;
    std::unordered_map<std::string, Function*> functions;
    std::unordered_map<std::string, Variable*> variables;

};


#endif //SKY_CLASS_H
