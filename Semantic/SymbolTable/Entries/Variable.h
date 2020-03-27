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

    Variable(Visibility, std::string, std::string, int, int);

    std::string &getType();

    std::string getRawType();

    int &getDimensions();

    std::string &getName();

    std::string getVisibilityString();

    Visibility getVisibility();

    friend std::ostream &operator<<(std::ostream &, Variable &);

    friend inline bool operator==(Variable &lhs, Variable &rhs) {
        return lhs.getType() == rhs.getType() &&
               lhs.getName() == rhs.getName() &&
               lhs.getDimensions() == rhs.getDimensions() &&
               lhs.getVisibilityString() == rhs.getVisibilityString();
    }

    inline void setPosition(int _position) { this->position = _position; }

    inline int getPosition() { return position; }

    inline bool isArray() { return dimensions != 0; }

private:

    std::string type;
    std::string name;
    int dimensions;
    Visibility visibility;
    int position;
};


#endif //SKY_VARIABLE_H
