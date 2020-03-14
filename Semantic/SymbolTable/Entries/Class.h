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

    Class(std::string, std::string, std::vector<std::string>);
    ~Class() = default;
    std::string &getName();
    std::string &getType();
    std::vector<std::string>& getInherits();
    std::unordered_map<std::string, std::vector<Function *> > &getFunctions();
    std::unordered_map<std::string, Variable *> &getVariables();

    Function* getFunction(std::string&, Function*);
    void addVariable(std::string&, Variable*);
    void addFunction(std::string&, Function*);
    friend std::ostream& operator<<(std::ostream&, Class&);

private:
    std::string name;
    std::string type;
    std::vector<std::string> inherits;
    std::unordered_map<std::string, std::vector<Function*> > functions;
    std::unordered_map<std::string, Variable*> variables;

};


#endif //SKY_CLASS_H
