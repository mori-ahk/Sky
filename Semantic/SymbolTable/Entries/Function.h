//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_FUNCTION_H
#define SKY_FUNCTION_H


#include <vector>
#include "Variable.h"
#include "Enums.h"
#include <iostream>

class Function {
public:

    Function(Enums::Enums , std::string, std::string, std::vector<Variable *>,
             std::vector<Variable *>, int);

    std::vector<Variable *> &getParams();

    std::vector<Variable *> &getLocalVars();

    Variable *getVariable(std::string &);

    std::string &getName();

    std::string &getReturnType();

    std::string getVisibilityString();

    Enums::Enums getVisibility();

    void addParam(Variable *);

    void addVariable(Variable *);

    static bool isParamsEqual(Function &, Function &);

    friend std::ostream &operator<<(std::ostream &, Function &);

    bool isDefined;

    friend inline bool operator==(Function &lhs, Function &rhs) {
        return lhs.getName() == rhs.getName() &&
               isParamsEqual(lhs, rhs) &&
               lhs.getReturnType() == rhs.getReturnType();
    }

    friend inline bool operator!=(Function &lhs, Function &rhs) {
        return !(lhs == rhs);
    }

    inline void setPosition(int _position) { this->position = _position; }

    inline int getPosition() { return position; }

    inline bool isPrivate() { return visibility == Enums::Enums::PRIVATE; }

    private:

    std::vector<Variable *> params;
    std::vector<Variable *> localVars;
    std::string name;
    std::string returnType;
    Enums::Enums visibility;
    int position;
};


#endif //SKY_FUNCTION_H
