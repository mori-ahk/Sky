//
// Created by Morteza Ahmadi on 2020-03-11.
//

#ifndef SKY_DETECTOR_H
#define SKY_DETECTOR_H

#include "../SymbolTable/SymbolTable.h"
#include <vector>
#include <string>
typedef std::vector<std::pair<std::string, std::string> > NamePair;
namespace Semantic {
    class Detector {
    public:
        Detector() {}

        NamePair detectUndefinedClassFunctions(Semantic::SymbolTable*);
        NamePair detectClassDuplicateFunctions(Semantic::SymbolTable*);
        NamePair detectClassOverloadedFunctions(Semantic::SymbolTable*);
        std::vector<std::string> detectFreeDuplicateFunctions(Semantic::SymbolTable*);
        std::vector<std::string> detectFreeOverloadedFunctions(Semantic::SymbolTable*);

    };
}

#endif //SKY_DETECTOR_H
