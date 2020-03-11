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
    UNDEFINEDFUNC,
    UNDECLAREDFUNC,
};

namespace Semantic {
    class Error : public std::exception {
    public:
        Error(Type type, std::string funcName = std::string(), std::string className = std::string()) {
            this->type = type;
            this->funcName = funcName;
            this->className = className;
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
                case Type::UNDEFINEDFUNC: {
                    std::string errorString =
                            "no definition for declared member function " + funcName + " for class " + className;
                    const char *_errorString = errorString.c_str();
                    return _errorString;
                }
                case Type::UNDECLAREDFUNC:
                    return "definition provided for undeclared member function";
            }
        }

    private:
        Type type;
        std::string funcName;
        std::string className;
    };
}

#endif //SKY_ERROR_H
