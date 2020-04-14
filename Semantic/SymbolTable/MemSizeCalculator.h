//
// Created by Morteza Ahmadi on 2020-04-09.
//

#ifndef SKY_MEMSIZECALCULATOR_H
#define SKY_MEMSIZECALCULATOR_H


#include "SymbolTable.h"

class MemSizeCalculator {
public:
    MemSizeCalculator() = default;

    explicit MemSizeCalculator(Semantic::SymbolTable *_symbolTable) {
        this->symbolTable = _symbolTable;
        calculate();
    }

private:
    void calculate();
    void calculateFunction(Function *);
    int calculateClass(Class *);
    int calculateVariable(Variable *);

    Semantic::SymbolTable *symbolTable;
};


#endif //SKY_MEMSIZECALCULATOR_H
