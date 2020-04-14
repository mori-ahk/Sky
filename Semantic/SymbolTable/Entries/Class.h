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

    int getOffset() const;

    void setOffset(int offset);

    int getSize() const;

    void setSize(int size);

    int getVariableOffset() const;

    std::vector<std::string> findShadowMembers(Class &);

    Function *getFunction(const std::string &, Function *) const;

    const Variable *getVariable(std::string &) const;

    void addVariable(const std::string &, Variable *);

    void addFunction(std::string &, Function *);

    friend std::ostream &operator<<(std::ostream &, Class &);

    inline void addOffset(int _size) { offset += _size; }

    inline void addSize(int _size) {
        sizes.push_back(_size);
        size += _size;
    }

    bool isMemSizeAlreadyCalculated = false;

private:
    std::string name;
    std::string type;
    std::vector<std::string> inherits;
    std::vector<int> sizes;
    std::unordered_map<std::string, std::vector<Function *> > functions;
    std::unordered_map<std::string, Variable *> variables;
    int position;
    int offset;
    int size;
};


#endif //SKY_CLASS_H
