//
// Created by Morteza Ahmadi on 2020-03-11.
//

#ifndef SKY_DETECTOR_H
#define SKY_DETECTOR_H

#include "../SymbolTable/SymbolTable.h"
#include "../SymbolTable/DependencyGraph.h"
#include <vector>
#include <string>
#include <unordered_set>

typedef std::vector<std::pair<std::string, std::string> > NamePair;
//typedef std::pair<std::string> error;

namespace Semantic {
    class Detector {
    public:
        Detector() = default;

        explicit Detector(Semantic::SymbolTable *_symbolTable) { this->symbolTable = _symbolTable; }

        void detectUndefinedClassFunctions();

        void detectFreeFunctionsErrors();

        void detectClassFunctionsErrors();

        bool detectCircularDependency();

        void detectShadowMembers(Class*);

        void detect();

        void addError(const std::string &);

        void initDependencyGraph(Semantic::SymbolTable *);

        std::vector<std::string> &getErrors();

    private:
        std::vector<std::string> errors;

        void handleUndefinedClassFunctions(NamePair &);

        void handleErrors(NamePair &, bool);

        void handleErrors(std::vector<std::string> &, bool);

        Semantic::SymbolTable *symbolTable;
        DependencyGraph *dependencyGraph;
    };
}

#endif //SKY_DETECTOR_H
