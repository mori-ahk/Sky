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

void Semantic::Detector::detectFreeFunctionsErrors(Semantic::SymbolTable* symbolTable) {
    std::vector<std::string> overloadedErrors;
    std::vector<std::string> duplicateErrors;
    for (auto& _functions : symbolTable->freeFunctions) {
        auto functions = _functions.second;
        for (int i = 0; i < functions.size(); i++) {
            for (int j = 0; j < functions.size() && i != j; j++) {
                auto funcName = functions.at(i)->getName();
                if (*functions.at(i) != *functions.at(j)) overloadedErrors.push_back(funcName);
                else duplicateErrors.push_back(funcName);
            }
        }
    }

    handleErrors(overloadedErrors, true);
    handleErrors(duplicateErrors, false);
}

void Semantic::Detector::detectClassFunctionsErrors(Semantic::SymbolTable* symbolTable) {
    NamePair overloadedErrors;
    NamePair duplicateErrors;
    for (auto& _class : symbolTable->classes) {
        for (auto& _functions : _class.second->getFunctions()) {
            auto functions = _functions.second;
            for (int i = 0; i < functions.size(); i++) {
                for (int j = 0; j < functions.size() && i != j; j++) {
                    auto pair = std::make_pair(functions.at(i)->getName(), _class.first);
                    if (*functions.at(i) != *functions.at(j)) overloadedErrors.push_back(pair);
                    else duplicateErrors.push_back(pair);
                }
            }
        }
    }

    handleErrors(overloadedErrors, true);
    handleErrors(duplicateErrors, false);
}
void Semantic::Detector::handleUndefinedClassFunctions(NamePair& undefined) {
    for (auto& e : undefined) {
        std::string errorString = "Undefined class functions " + e.first + " on class " + e.second;
        auto pair = std::make_pair(errorString, 0);
        addError(pair);
    }
}

void Semantic::Detector::handleErrors(NamePair& _errors, bool isOverloaded) {
    for (auto& e : _errors) {
        std::string errorString = isOverloaded ? "Overloaded" : "Duplicate";
        errorString += " class function " + e.first + " on class " + e.second;
        auto pair = std::make_pair(errorString, 0);
        addError(pair);
    }
}

void Semantic::Detector::handleErrors(std::vector<std::string>& _errors, bool isOverloaded) {
    for (auto& e : _errors) {
        std::string errorString = isOverloaded ? "Overloaded" : "Duplicate";
        errorString += " free function " + e;
        auto pair = std::make_pair(errorString, 0);
        addError(pair);
    }
}

void Semantic::Detector::addError(const error& _error) {
    errors.push_back(_error);
}

void Semantic::Detector::detect(SymbolTable * symbolTable) {
    detectUndefinedClassFunctions(symbolTable);
    detectFreeFunctionsErrors(symbolTable);
    detectClassFunctionsErrors(symbolTable);
}

std::vector<error>& Semantic::Detector::getErrors() {
    return errors;
}