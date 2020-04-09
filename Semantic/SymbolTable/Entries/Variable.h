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

    Variable(Enums::Visibility, std::string, std::string, int, int);

    const std::string &getType() const ;

    std::string getRawType() const ;

    const int &getDimensions() const ;

    const std::string &getName() const;

    std::string getVisibilityString() const;

    Enums::Visibility getVisibility() const;

    Enums::Kind getKind() const;

    friend std::ostream &operator<<(std::ostream &, Variable &);

    friend inline bool operator==(Variable &lhs, Variable &rhs) {
        return lhs.getType() == rhs.getType() &&
               lhs.getName() == rhs.getName() &&
               lhs.getDimensions() == rhs.getDimensions() &&
               lhs.getVisibilityString() == rhs.getVisibilityString();
    }

    inline void setPosition(int _position) { this->position = _position; }

    inline int getPosition() const { return position; }

    inline bool isArray() const { return dimensions != 0; }

    inline bool isPrivate() const { return visibility == Enums::Visibility::PRIVATE; }

private:

    std::string type;
    std::string name;
    int dimensions;
    Enums::Visibility visibility;
    Enums::Kind kind;
    int position;
};


#endif //SKY_VARIABLE_H
