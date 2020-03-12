//
// Created by Morteza Ahmadi on 2020-03-11.
//

#include "Detector.h"
#include <string>
NamePair Semantic::Detector::detectUndefinedClassFunctions(Semantic::SymbolTable* symbolTable) {
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
    return undefinedFunctions;
}

NamePair Semantic::Detector::detectClassDuplicateFunctions(Semantic::SymbolTable* symbolTable) {
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

    return classDuplicateFunctions;
}

NamePair Semantic::Detector::detectClassOverloadedFunctions(Semantic::SymbolTable* symbolTable) {
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

    return classOverloadedFunctions;
}

std::vector<std::string> Semantic::Detector::detectFreeDuplicateFunctions(Semantic::SymbolTable* symbolTable) {
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

    return freeDuplicateFunctions;
}

std::vector<std::string> Semantic::Detector::detectFreeOverloadedFunctions(Semantic::SymbolTable* symbolTable) {
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

    return freeDuplicateFunctions;
}