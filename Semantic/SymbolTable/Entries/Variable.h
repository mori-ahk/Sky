//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_VARIABLE_H
#define SKY_VARIABLE_H

#include <string>
#include <vector>
#include "Visibility.h"
#include <iostream>

class Variable {
public:

    Variable(Visibility, std::string, std::string, std::vector<int>, int);

    std::string &getType();

    std::vector<int> &getDimensions();

    std::string &getName();

    std::string getVisibilityString();

    std::string getDimsString();

    Visibility getVisibility();

    friend std::ostream &operator<<(std::ostream &, Variable &);

    friend inline bool operator==(Variable &lhs, Variable &rhs) {
        return lhs.getType() == rhs.getType() &&
               lhs.getName() == rhs.getName() &&
               lhs.getDimsString() == rhs.getDimsString() &&
               lhs.getVisibilityString() == rhs.getVisibilityString();
    }

    inline void setPosition(int _position) { this->position = _position; }

    inline int getPosition() { return position; }

private:

    std::string type;
    std::string name;
    std::vector<int> dimensions;
    Visibility visibility;
    int position;
};


#endif //SKY_VARIABLE_H
