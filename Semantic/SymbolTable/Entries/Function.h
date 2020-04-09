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

    Function(Enums::Visibility , std::string, std::string, std::vector<Variable *>,
             std::vector<Variable *>, int);

    const std::vector<Variable *> &getParams() const ;

    const std::vector<Variable *> &getLocalVars() const;

    const Variable *getVariable(std::string &) const;

    const std::string &getName() const;

    const std::string &getReturnType() const;

    std::string getVisibilityString() const;

    Enums::Visibility getVisibility() const;

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

    inline bool isPrivate() { return visibility == Enums::Visibility::PRIVATE; }


    private:

    std::vector<Variable *> params;
    std::vector<Variable *> localVars;
    std::string name;
    std::string returnType;
    Enums::Visibility visibility;
    int position;
};


#endif //SKY_FUNCTION_H
