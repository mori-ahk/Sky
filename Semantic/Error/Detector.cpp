//
// Created by Morteza Ahmadi on 2020-03-11.
//

#include "Detector.h"
#include <string>

void Semantic::Detector::detectUndefinedClassFunctions(Semantic::SymbolTable* symbolTable) {
    NamePair undefinedFunctions;
    for (auto& _class : symbolTable->classes) {
        for (auto& _function: _class.second->getFunctions()) {
            for (auto& _f : _function.second) {
                if (!_f->isDefined) {
                    auto pair = std::make_pair(_f->getName(), _class.first);
                    undefinedFunctions.push_back(pair);
                }
            }
        }
    }
    handleUndefinedClassFunctions(undefinedFunctions);
}

void Semantic::Detector::detectClassDuplicateFunctions(Semantic::SymbolTable* symbolTable) {
    NamePair classDuplicateFunctions;
    for (auto& _class : symbolTable->classes) {
        for (auto& _functions : _class.second->getFunctions()) {
            auto functions = _functions.second;
            for (int i = 0; i < functions.size(); i++) {
                for (int j = 0; j < functions.size() && i != j; j++) {
                    if (*functions.at(i) == *functions.at(j)) {
                        auto pair = std::make_pair(functions.at(i)->getName(), _class.first);
                        classDuplicateFunctions.push_back(pair);
                    }
                }
            }
        }
    }

    handleClassDuplicate(classDuplicateFunctions);
}

void Semantic::Detector::detectClassOverloadedFunctions(Semantic::SymbolTable* symbolTable) {
    NamePair classOverloadedFunctions;
    for (auto& _class : symbolTable->classes) {
        for (auto& _functions : _class.second->getFunctions()) {
            auto functions = _functions.second;
            for (int i = 0; i < functions.size(); i++) {
                for (int j = 0; j < functions.size() && i != j; j++) {
                    if (*functions.at(i) == *functions.at(j)) continue;
                    else {
                        auto pair = std::make_pair(functions.at(i)->getName(), _class.first);
                        classOverloadedFunctions.push_back(pair);
                    }
                }
            }
        }
    }

    handleClassOverloaded(classOverloadedFunctions);
}

void Semantic::Detector::detectFreeDuplicateFunctions(Semantic::SymbolTable* symbolTable) {
    std::vector<std::string> freeDuplicateFunctions;
    for (auto& _functions : symbolTable->freeFunctions) {
        auto functions = _functions.second;
        for (int i = 0; i < functions.size(); i++) {
            for (int j = 0; j < functions.size() && i != j; j++) {
                if (*functions.at(i) == *functions.at(j))  {
                    freeDuplicateFunctions.push_back(functions.at(i)->getName());
                }
            }
        }
    }

    handleFreeDuplicate(freeDuplicateFunctions);
}

void Semantic::Detector::detectFreeOverloadedFunctions(Semantic::SymbolTable* symbolTable) {
    std::vector<std::string> freeDuplicateFunctions;
    for (auto& _functions : symbolTable->freeFunctions) {
        auto functions = _functions.second;
        for (int i = 0; i < functions.size(); i++) {
            for (int j = 0; j < functions.size() && i != j; j++) {
                if (*functions.at(i) == *functions.at(j)) continue;
                else freeDuplicateFunctions.push_back(functions.at(i)->getName());
            }
        }
    }

    handleFreeOverloaded(freeDuplicateFunctions);
}

void Semantic::Detector::handleClassDuplicate(NamePair& duplicates) {
    for (auto& e : duplicates) {
        std::string errorString = "Duplicate class function " + e.first + " on class " + e.second;
        auto pair = std::make_pair(errorString, 0);
        addError(pair);
    }
}

void Semantic::Detector::handleClassOverloaded(NamePair& duplicates) {
    for (auto& e : duplicates) {
        std::string errorString = "Overloaded class function " + e.first + " on class " + e.second;
        auto pair = std::make_pair(errorString, 0);
        addError(pair);
    }
}

void Semantic::Detector::handleUndefinedClassFunctions(NamePair& undefined) {
    for (auto& e : undefined) {
        std::string errorString = "Undefined class functions " + e.first + " on class " + e.second;
        auto pair = std::make_pair(errorString, 0);
        addError(pair);
    }
}

void Semantic::Detector::handleFreeDuplicate(std::vector<std::string>& duplicates) {
    for (auto& e : duplicates) {
        std::string errorString = "Duplicate free function " + e;
        auto pair = std::make_pair(errorString, 0);
        addError(pair);
    }
}

void Semantic::Detector::handleFreeOverloaded(std::vector<std::string> & duplicates) {
    for (auto& e : duplicates) {
        std::string errorString = "Overloaded free function " + e;
        auto pair = std::make_pair(errorString, 0);
        addError(pair);
    }
}


void Semantic::Detector::addError(const error& _error) {
    errors.push_back(_error);
}

void Semantic::Detector::detect(SymbolTable * symbolTable) {
    detectUndefinedClassFunctions(symbolTable);
    detectClassOverloadedFunctions(symbolTable);
    detectFreeOverloadedFunctions(symbolTable);
    detectFreeDuplicateFunctions(symbolTable);
    detectClassDuplicateFunctions(symbolTable);
}

std::vector<error>& Semantic::Detector::getErrors() {
    return errors;
}