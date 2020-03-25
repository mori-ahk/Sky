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
            DuplicateDataMember(std::string varName, int position) : Error() {
                this->varName = varName;
                this->position = position;
            }

            const char *what() const throw() {
                std::string errorString = "duplicate data member " + varName + " at line " + std::to_string(position);
                const char *_errorString = errorString.c_str();
                return _errorString;
            }
        private:
            std::string varName;
            int position;
        };

        class DuplicateFuncParam : public Error {
        public:
            DuplicateFuncParam(int position) : Error() {
                this->position = position;
            }

            const char *what() const throw() {
                std::string errorString = "duplicate func param with the same name at line " + std::to_string(position);
                const char *_errorString = errorString.c_str();
                return _errorString;
            }
        private:
            int position;
        };

        class DuplicateClassDecl : public Error {
        public:
            DuplicateClassDecl(std::string className) : Error() {
                this->className = className;
            }

            const char *what() const throw() {
                std::string errorString = "multi declared class name " + className;
                const char *_errorString = errorString.c_str();
                return _errorString;
            }
        private:
            std::string className;
        };

        class UndefinedFunction : public Error {
        public:
            UndefinedFunction(std::string funcName, std::string className) : Error() {
                this->funcName = funcName;
                this->className = className;
            }

            const char *what() const throw() {
                std::string errorString =
                        "no definition for declared member function " + funcName + " for class " + className;
                const char *_errorString = errorString.c_str();
                return _errorString;
            }

        private:
            std::string funcName;
            std::string className;
        };

        class UndeclaredFunction : public Error {
        public:
            UndeclaredFunction(std::string funcName, int position) : Error() {
                this->funcName = funcName;
                this->position = position;
            }

            const char *what() const throw() {
                std::string errorString = "definition provided for undeclared member function " + funcName + " at line " + std::to_string(position);
                const char *_errorString = errorString.c_str();
                return _errorString;
            }

        private:
            std::string funcName;
            int position;
        };

        class UndeclaredClass : public Error {
        public:
            UndeclaredClass(std::string className) : Error() {
                this->className = className;
            }

            const char *what() const throw() {
                std::string errorString = "use of undeclared class " + className;
                const char *_errorString = errorString.c_str();
                return _errorString;
            }

        private:
            std::string className;
        };

        class DuplicateFunction : public Error {
        public:
            DuplicateFunction(std::string funcName, int position) : Error() {
                this->funcName = funcName;
                this->position = position;
            }

            const char *what() const throw() {
                std::string errorString = "Found duplicate function declaration of " + funcName + " at line " + std::to_string(position);
                const char *_errorString = errorString.c_str();
                return _errorString;
            }

        private:
            std::string funcName;
            int position;
        };

        class UndeclaredLocalVariable : public Error {
        public:
            UndeclaredLocalVariable(std::string varName) : Error() {
                this->varName = varName;
            }

            const char *what() const throw() {
                std::string errorString = "Use of undeclared local variable " + varName;
                const char *_errorString = errorString.c_str();
                return _errorString;
            }

        private:
            std::string varName;
        };

        class UndeclaredClassVariable : public Error {
        public:
            UndeclaredClassVariable(std::string varName) : Error() {
                this->varName = varName;
            }

            const char *what() const throw() {
                std::string errorString = "Use of undeclared class variable " + varName;
                const char* _errorString = errorString.c_str();
                return _errorString;
            }

        private:
            std::string varName;

        };
    }
}

#endif //SKY_ERROR_H
