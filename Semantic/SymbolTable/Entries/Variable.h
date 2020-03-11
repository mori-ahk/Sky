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

    Variable(Visibility visibility, std::string name, std::string type, std::vector<int> dimensions);

    std::string& getType();
    std::vector<int>& getDimensions();
    std::string& getName();
    std::string getVisibilityString();
    std::string getDimsString();
    Visibility getVisibility();
    friend std::ostream& operator<<(std::ostream&, Variable&);
private:

    std::string type;
    std::string name;
    std::vector<int> dimensions;
    Visibility visibility;
};


#endif //SKY_VARIABLE_H
