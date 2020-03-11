//
// Created by Morteza Ahmadi on 2020-03-10.
//

#ifndef SKY_ERROR_H
#define SKY_ERROR_H

#include <exception>
#include <iostream>

enum class Type {
    MULTDECLDATAMEMEBER,
    MULTDECLFUNCPARAM,
    MULTDECCLASS,
    SAMEFUNCTION,
    DEFLESSFUNC,
    DECLESSFUNC,
};

namespace Semantic {
    class Error : public std::exception {
    public:
        Error(Type type) {
            this->type = type;
        }

        const char *what() const throw() {
            switch (type) {
                case Type::MULTDECLDATAMEMEBER:
                    return "multi declared data member";
                case Type::MULTDECLFUNCPARAM:
                    return "multi declared func param with the same name";
                case Type::MULTDECCLASS:
                    return "multi declared class";
                case Type::SAMEFUNCTION:
                    return "same function with the same variable!";
                case Type::DEFLESSFUNC:
                    return "no definition for declared member function";
                case Type::DECLESSFUNC:
                    return "definition provided for undeclared member function";
            }
        }

    private:
        Type type;
    };
}

#endif //SKY_ERROR_H
