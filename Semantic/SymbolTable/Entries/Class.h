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

    Class(std::string, std::string, std::vector<std::string>, int);

    ~Class() = default;

    const std::string &getName() const;

    const std::string &getType() const;

    const std::vector<std::string> &getInherits() const;

    const std::unordered_map<std::string, std::vector<Function *> > &getFunctions() const;

    const std::unordered_map<std::string, Variable *> &getVariables() const;

    std::vector<std::string> findShadowMembers(Class &);

    Function *getFunction(const std::string &, Function *) const;

    const Variable *getVariable(std::string &) const;

    void addVariable(const std::string &, Variable *);

    void addFunction(std::string &, Function *);

    friend std::ostream &operator<<(std::ostream &, Class &);

    inline void setPosition(int _position) { this->position = _position; }

    inline int getPosition() { return position; }

private:
    std::string name;
    std::string type;
    std::vector<std::string> inherits;
    std::unordered_map<std::string, std::vector<Function *> > functions;
    std::unordered_map<std::string, Variable *> variables;
    int position;
};


#endif //SKY_CLASS_H
