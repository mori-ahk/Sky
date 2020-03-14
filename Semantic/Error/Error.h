//
// Created by Morteza Ahmadi on 2020-03-10.
//

#ifndef SKY_ERROR_H
#define SKY_ERROR_H

#include <exception>
#include <iostream>

namespace Semantic {

    class Error : public std::exception {
    public:
        Error() = default;
    };

    namespace Err {
        class DuplicateDataMember : public Error {
        public:
            DuplicateDataMember() : Error() {}

            const char *what() const throw() {
                return "multi declared data member";
            }
        };

        class DuplicateFuncParam : public Error {
        public:
            DuplicateFuncParam() : Error() {}

            const char *what() const throw() {
                return "multi declared func param with the same name";
            }
        };

        class DuplicateClassDecl : public Error {
        public:
            DuplicateClassDecl() : Error() {}

            const char *what() const throw() {
                return "multi declared class";
            }
        };

        class UndefinedFunction : public Error {
        public:
            UndefinedFunction(std::string funcName, std::string className) : Error() {
                this->funcName = funcName;
                this->className = className;
            }

            const char *what() const throw() {
                std::string errorString = "no definition for declared member function " + funcName + " for class " + className;
                const char* _errorString = errorString.c_str();
                return _errorString;
            }

        private:
            std::string funcName;
            std::string className;
        };

        class UndeclaredFunction : public Error {
        public:
            UndeclaredFunction(std::string funcName) : Error() {
                this->funcName = funcName;
            }

            const char *what() const throw() {
                std::string errorString = "definition provided for undeclared member function " + funcName;
                const char* _errorString = errorString.c_str();
                return _errorString;
            }
        private:
            std::string funcName;
        };

        class UndeclaredClass : public Error {
        public:
            UndeclaredClass(std::string className) : Error() {
                this->className = className;
            }

            const char *what() const throw() {
                std::string errorString = "use of undeclared class " + className;
                const char* _errorString = errorString.c_str();
                return  _errorString;
            }

        private:
            std::string className;
        };

        class DuplicateFunction : public Error {
        public:
            DuplicateFunction(std::string funcName) : Error() {
                this->funcName = funcName;
            }

            const char *what() const throw() {
                std::string errorString = "Found duplicate function declaration of " + funcName;
                const char* _errorString = errorString.c_str();
                return _errorString;
            }

        private:
            std::string funcName;
        };

    }
}

#endif //SKY_ERROR_H
