//
// Created by Morteza Ahmadi on 2020-03-05.
//

#ifndef SKY_VARIABLE_H
#define SKY_VARIABLE_H

#include <string>
#include <vector>
#include "Enums.h"
#include <iostream>

class Variable {
public:

    Variable(Enums::Enums, std::string, std::string, int, int);

    std::string &getType();

    std::string getRawType();

    int &getDimensions();

    std::string &getName();

    std::string getVisibilityString();

    Enums::Enums getVisibility();

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

    inline bool isPrivate() { return visibility == Enums::Enums::PRIVATE; }

private:

    std::string type;
    std::string name;
    int dimensions;
    Enums::Enums visibility;
    int position;
};


#endif //SKY_VARIABLE_H
