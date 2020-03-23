//
// Created by Morteza Ahmadi on 2020-03-11.
//

#include "Detector.h"
#include <string>

void Semantic::Detector::initDependencyGraph(Semantic::SymbolTable *_symbolTable) {
    try { this->dependencyGraph = new DependencyGraph(_symbolTable); }
    catch (Semantic::Err::UndeclaredClass &undeclaredClass) { throw; }
}

void Semantic::Detector::detectUndefinedClassFunctions() {
    NamePair undefinedFunctions;
    for (const auto &_class : symbolTable->classes) {
        for (const auto &_function: _class.second->getFunctions()) {
            for (const auto &_f : _function.second) {
                if (!_f->isDefined) {
                    auto pair = std::make_pair(_f->getName(), _class.first);
                    undefinedFunctions.push_back(pair);
                }
            }
        }
    }
    handleUndefinedClassFunctions(undefinedFunctions);
}

void Semantic::Detector::detectFreeFunctionsErrors() {
    std::vector<std::string> overloadedErrors;
    std::vector<std::string> duplicateErrors;
    for (const auto &_functions : symbolTable->freeFunctions) {
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

void Semantic::Detector::detectClassFunctionsErrors() {
    NamePair overloadedErrors;
    NamePair duplicateErrors;
    for (const auto &_class : symbolTable->classes) {
        for (const auto &_functions : _class.second->getFunctions()) {
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

bool Semantic::Detector::detectCircularDependency() {
    std::unordered_set<std::string> visited;
    for (auto &node : dependencyGraph->nodes) {
        std::string className = node->getName();
        if (visited.find(className) == visited.end()) {
            std::unordered_set<std::string> visiting;
            auto pair = dependencyGraph->dfs(className, visiting, visited);
            if (!pair.first.empty() && !pair.second.empty()) {
                std::string errorString = "Circular dependencies between " + pair.first + " and " + pair.second;
                addError(errorString);
                return true;
            }

            //union the visiting and visited set
            auto _visiting = std::unordered_set<std::string>(visiting);
            visited.insert(_visiting.begin(), _visiting.end());
        }
    }
    return false;
}

void Semantic::Detector::detectShadowMembers(Class *parent) {
    if (parent->getInherits().empty()) return;
    for (const auto& c : parent->getInherits()) {
        detectShadowMembers(symbolTable->classes.at(c));
        auto shadowMessages = symbolTable->classes.at(c)->findShadowMembers(*parent);
        if (!shadowMessages.empty()) for (const auto& s : shadowMessages) addWarning(s);
    }
}

void Semantic::Detector::handleUndefinedClassFunctions(NamePair &undefined) {
    for (const auto &e : undefined) {
        std::string errorString = "Undefined class functions " + e.first + " on class " + e.second;
        addError(errorString);
    }
}

void Semantic::Detector::handleErrors(NamePair &_errors, bool isOverloaded) {
    for (const auto &e : _errors) {
        std::string warningString = isOverloaded ? "Overloaded" : "Duplicate";
        warningString += " class function " + e.first + " on class " + e.second;
        addWarning(warningString);
    }
}

void Semantic::Detector::handleErrors(std::vector<std::string> &_errors, bool isOverloaded) {
    for (const auto &e : _errors) {
        std::string warningString = isOverloaded ? "Overloaded" : "Duplicate";
        warningString += " free function " + e;
        addWarning(warningString);
    }
}

void Semantic::Detector::addError(const std::string &_error) {
    errors.push_back(_error);
}

void Semantic::Detector::addWarning(const std::string &_warning) {
    warnings.push_back(_warning);
}

void Semantic::Detector::detect() {
    //If an undeclared class found while building the dependency graph, the detect function returns
    //and will not proceed with other detections.
    try { initDependencyGraph(symbolTable); }
    catch (Semantic::Err::UndeclaredClass &undeclaredClass) {
        addError(undeclaredClass.what());
        return;
    }

    bool containsCircularDependency = detectCircularDependency();

    //If contains circular dependency, shadow member function gets stuck in an infinite loop.
    if (!containsCircularDependency) {
        for (const auto &c : symbolTable->classes) {
            detectShadowMembers(c.second);
        }
    }

    detectUndefinedClassFunctions();
    detectFreeFunctionsErrors();
    detectClassFunctionsErrors();
}

std::vector<std::string> &Semantic::Detector::getErrors() {
    return errors;
}