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
        Detector() {}

        void detectUndefinedClassFunctions(Semantic::SymbolTable*);
        void detectClassDuplicateFunctions(Semantic::SymbolTable*);
        void detectClassOverloadedFunctions(Semantic::SymbolTable*);
        void detectFreeDuplicateFunctions(Semantic::SymbolTable*);
        void detectFreeOverloadedFunctions(Semantic::SymbolTable*);
        void detect(SymbolTable*);
        void addError(error);

        std::vector<error>& getErrors();

    private:
        std::vector<error> errors;
        void handleClassDuplicate(NamePair&);
        void handleClassOverloaded(NamePair&);
        void handleUndefinedClassFunctions(NamePair&);
        void handleFreeDuplicate(std::vector<std::string>&);
        void handleFreeOverloaded(std::vector<std::string>&);
    };
}

#endif //SKY_DETECTOR_H
