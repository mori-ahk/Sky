//
// Created by Morteza Ahmadi on 2020-04-09.
//

#include "MemSizeCalculator.h"

void MemSizeCalculator::calculate() {
    for (auto &_class : symbolTable->classes) calculateClass(_class.second);
    for (auto &functions: symbolTable->freeFunctions)
        for (auto &function : functions.second) calculateFunction(function);

    //calculate mem size for main function
    calculateFunction(symbolTable->main);
}

int MemSizeCalculator::calculateClass(Class *_class) {
    if (_class->isMemSizeAlreadyCalculated) return _class->getSize();
    for (auto &inherit : _class->getInherits()) {
        int classSize = calculateClass(symbolTable->getClass(inherit));
        _class->addSize(classSize);
    }

    for (auto &var : _class->getVariables()) {
        int variableSize = calculateVariable(var.second);
        _class->addSize(variableSize);
        var.second->setSize(variableSize);
        var.second->setOffset(_class->getVariableOffset());
    }

    _class->setOffset(_class->getSize());
    _class->isMemSizeAlreadyCalculated = true;

    for (auto &functions : _class->getFunctions())
        for (auto &function : functions.second) calculateFunction(function);

    return _class->getSize();
}

void MemSizeCalculator::calculateFunction(Function *function) {
    for (auto &var : function->getLocalVars()) {
        int variableSize = calculateVariable(var);
        function->addSize(variableSize);
        var->setSize(variableSize);
        var->setOffset(function->getVariableOffset());
    }

    function->setOffset(function->getSize());
}

int MemSizeCalculator::calculateVariable(Variable *variable) {
    if (variable->isTypeId()) {
        auto classToCalculate = symbolTable->getClass(variable->getRawType());
        if (classToCalculate->isMemSizeAlreadyCalculated) return classToCalculate->getSize();
        else { return calculateClass(classToCalculate); }
    }
    int size = 4;
    if (variable->isArray())
        for (int _size : variable->getArraySize()) size *= _size;
    variable->setSize(size);
    return size;
}

