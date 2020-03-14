//
// Created by Morteza Ahmadi on 2020-03-11.
//

#ifndef SKY_DETECTOR_H
#define SKY_DETECTOR_H

#include "../SymbolTable/SymbolTable.h"
#include <vector>
#include <string>

typedef std::vector<std::pair<std::string, std::string> > NamePair;
typedef std::pair<std::string, int> error;

namespace Semantic {
    class Detector {
    public:
        Detector() = default;

        void detectUndefinedClassFunctions(Semantic::SymbolTable*);
        void detectFreeFunctionsErrors(Semantic::SymbolTable*);
        void detectClassFunctionsErrors(Semantic::SymbolTable*);
        void detect(SymbolTable*);
        void addError(const error&);

        std::vector<error>& getErrors();

    private:
        std::vector<error> errors;
        void handleUndefinedClassFunctions(NamePair&);
        void handleErrors(NamePair&, bool);
        void handleErrors(std::vector<std::string>&, bool);
    };
}

#endif //SKY_DETECTOR_H
