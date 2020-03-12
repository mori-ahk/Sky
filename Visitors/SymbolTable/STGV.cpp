//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "STGV.h"
#include <iostream>
#include <vector>


STGV::STGV(AST::ASTNode* root) {
    this->symbolTable = new Semantic::SymbolTable();
    this->detector = new Semantic::Detector();
    root->getChildren().at(0)->accept(*this);
}
void STGV::visit(Program *node) {
    for(auto child : node->getChildren()) {
        child->accept(*this);
    }
}

void STGV::visit(Local *node) {}

void STGV::visit(FuncDef *node) {
    std::string namespaceName;

    auto signature = node->getChild(0);
    auto funcBody = node->getChild(1);
    auto isClassFunc = [&signature]() {
        return signature->getChildren().size() == 4;
    };

    //if the function belongs to a class and has a namespace;
    if (isClassFunc()) namespaceName = signature->getChild(0)->getName();

    std::string funcName;
    if (isClassFunc()) funcName = signature->getChild(1)->getName();
    else funcName = signature->getChild(0)->getName();

    std::string returnType = isClassFunc() ? signature->getChild(3)->getName() : signature->getChild(2)->getName();
    Function* function = new Function(Visibility::PUBLIC, funcName, returnType, {}, {});

    //iterating on params
    auto params = isClassFunc() ? signature->getChild(2) : signature->getChild(1);

    for (auto param: params->getChildren()) {
        Variable *variable = createVar(param);

        //throw a semantic error if `variable` is a duplicate param in the `function`
        try {
            function->addParam(variable);
        } catch (Semantic::Err::DuplicateFuncParam& duplicateParam) {
            int position = param->getChild(1)->getLineNumber();
            auto pair = std::make_pair(std::string(duplicateParam.what()), position);
            symbolTable->addError(pair);
        }
    }

    //check if the class function signature and defined function signature match.
    if (isClassFunc()) {
        try {
            auto classFunction = symbolTable->getClass(namespaceName)->getFunction(funcName);
            symbolTable->doesMatch(*classFunction, *function);
            classFunction->isDefined = true;
        } catch (Semantic::Err::UndeclaredClass& undeclaredClass) {
            int position = signature->getChild(0)->getLineNumber();
            auto pair = std::make_pair(std::string(undeclaredClass.what()), position);
            symbolTable->addError(pair);
            return;
        } catch (Semantic::Err::UndeclaredFunction& undeclaredFunc) {
            int position = signature->getChild(0)->getLineNumber();
            auto pair = std::make_pair(std::string(undeclaredFunc.what()), position);
            symbolTable->addError(pair);
            return;
        }
    }

    //iterating on local vars
    auto localVars = funcBody->getChild(0);
    for (auto localVar : localVars->getChildren()) {
        Variable* variable = createVar(localVar);

        //throw a semantic error if `variable` is a duplicate variable in the `function`'s local scope.
        try {
            function->addVariable(variable);
        } catch (Semantic::Err::DuplicateDataMember& duplicateLocalVar) {
            int position = localVar->getChild(1)->getLineNumber();
            auto pair = std::make_pair(std::string(duplicateLocalVar.what()), position);
            symbolTable->addError(pair);
        }

        //fetching the class that this function corresponds to and add local variable to its scope
        if (isClassFunc()) {
            auto classFunction = symbolTable->classes.at(namespaceName)->getFunction(funcName);
            classFunction->addVariable(variable);
        }
    }

    if (!isClassFunc()) symbolTable->addFunction(funcName, function);

}

void STGV::visit(VarDecl *node) {
    Variable* variable = createVar(node);
    try {
        symbolTable->getClass(node->getParent()->getName())->addVariable(variable->getName(), variable);
    } catch (Semantic::Err::UndeclaredClass& undeclaredClass) {
        int position = node->getParent()->getLineNumber();
        auto pair = std::make_pair(std::string(undeclaredClass.what()), position);
        symbolTable->addError(pair);
    } catch (Semantic::Err::DuplicateDataMember& duplicateDataMember) {
        int position = node->getChild(1)->getLineNumber();
        auto pair = std::make_pair(std::string(duplicateDataMember.what()), position);
        symbolTable->addError(pair);
    }
}

void STGV::visit(ArrayDim *node) {}

void STGV::visit(FuncBody *node) {}

void STGV::visit(FuncDecl *node) {
    std::string visibilityString = node->getChild(0)->getName();
    Visibility  visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
    std::string funcName =  node->getChild(1)->getName();
    std::string returnType = node->getChild(3)->getName();
    Function* function = new Function(visibility, funcName, returnType, {}, {});

    try {
        symbolTable->getClass(node->getParent()->getName())->addFunction(funcName, function);
    } catch (Semantic::Err::UndeclaredClass& undeclaredClass) {
        int position = node->getChild(1)->getLineNumber();
        auto pair = std::make_pair(std::string(undeclaredClass.what()), position);
        symbolTable->addError(pair);
    }

    //setting the parent of `funcName` node to `className` node
    node->getChild(1)->setParent(node->getParent());
    //setting the parent of `params` node to `funcName` node
    node->getChild(2)->setParent(node->getChild(1));

    node->getChild(2)->accept(*this);
}

void STGV::visit(ClassDecl *node) {
    //Creating a class entry
    std::string className = node->getChild(0)->getName();
    std::string inherits = "";
    //constructing a string indicating all the parent class
    for (auto child : node->getChild(1)->getChildren()) {
        inherits += child->getName() + " ";
    }

    Class* classEntry = new Class(className, className, inherits);
    try {
        symbolTable->addClass(className, classEntry);
    } catch (Semantic::Err::DuplicateClassDecl& duplicateClassDecl) {
        int position = node->getChild(0)->getLineNumber();
        auto pair = std::make_pair(std::string(duplicateClassDecl.what()), position);
        symbolTable->addError(pair);
    }

    for (auto child : node->getChild(2)->getChildren()) {
       //setting the parent of each member in `MEMBERDECLARATIONS` to `className` node
       child->setParent(node->getChild(0));
       child->accept(*this);
    }

    auto duplicateClassFunctions = detector->detectClassDuplicateFunctions(symbolTable);
    auto overloadedClassFunctions = detector->detectClassOverloadedFunctions(symbolTable);
    handleClassDuplicate(duplicateClassFunctions);
    handleClassOverloaded(overloadedClassFunctions);
}

void STGV::visit(ClassDecls *node) {
    for(auto child : node->getChildren()) {
        child->accept(*this);
    }
}

void STGV::visit(FuncParams *node) {
    for(auto child: node->getChildren()) {
        //setting the parent of each `param` node to `funcName` node
        child->setParent(node->getParent());

        Variable* variable = createVar(child);
        try {
            symbolTable->getClass(node->getParent()->getParent()->getName())->getFunction(
                    node->getParent()->getName())->addParam(variable);
        } catch (Semantic::Err::UndeclaredClass& undeclaredClass) {
            int position = node->getParent()->getLineNumber();
            auto pair = std::make_pair(std::string(undeclaredClass.what()), position);
            symbolTable->addError(pair);
        }
    }
}

void STGV::visit(MainFunc* node) {
    auto duplicateFreeFunctions = detector->detectFreeDuplicateFunctions(symbolTable);
    auto overloadedFreeFunctions = detector->detectFreeOverloadedFunctions(symbolTable);
    handleFreeDuplicate(duplicateFreeFunctions);
    handleFreeOverloaded(overloadedFreeFunctions);
    auto funcBody = node->getChild(0);
    auto localVars = funcBody->getChild(0);

    for(auto var : localVars->getChildren()) {
        Variable* variable = createVar(var);
        try {
            symbolTable->main->addVariable(variable);
        } catch (Semantic::Err::DuplicateDataMember& duplicateLocalVar) {
            int position = var->getChild(1)->getLineNumber();
            auto pair = std::make_pair(std::string(duplicateLocalVar.what()), position);
            symbolTable->addError(pair);
        }
    }
}

void STGV::visit(AST::ASTNode *node) {
    for(auto child : node->getChildren()) {
        child->setParent(node->getParent());
        child->accept(*this);
    }
}


Variable* STGV::createVar(AST::ASTNode* node) {
    int startIndex = node->getChildren().size() == 4 ? 1 : 0;
    Visibility  visibility = Visibility::PRIVATE;

    if (node->getChildren().size() == 4) {
        std::string visibilityString = node->getChildren().at(0)->getName();
        Visibility visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
    }

    std::string varName = node->getChild(startIndex++)->getName();
    std::string type = node->getChild(startIndex++)->getName();
    std::vector<int> dimensions;

    auto dimNodeToIterate = node->getChildren().size() == 4 ? node->getChild(3) : node->getChild(2);
    for (auto& arrayDimensionChild: dimNodeToIterate->getChildren()) {
        try {
            int dimension = std::stoi(arrayDimensionChild->getChild(0)->getName());
            dimensions.push_back(dimension);
        } catch (const std::invalid_argument& invalid_argument) {}
    }

    return new Variable(visibility, type, varName, dimensions);
}


void STGV::handleClassDuplicate(NamePair& duplicates) {
    for (auto& e : duplicates) {
        std::string errorString = "Duplicate class function " + e.first + " on class " + e.second;
        auto pair = std::make_pair(errorString, 0);
        symbolTable->addError(pair);
    }
}

void STGV::handleClassOverloaded(NamePair& duplicates) {
    for (auto& e : duplicates) {
        std::string errorString = "Overloaded class function " + e.first + " on class " + e.second;
        auto pair = std::make_pair(errorString, 0);
        symbolTable->addError(pair);
    }
}

void STGV::handleFreeDuplicate(std::vector<std::string>& duplicates) {
    for (auto& e : duplicates) {
        std::string errorString = "Duplciate free function " + e;
        auto pair = std::make_pair(errorString, 0);
        symbolTable->addError(pair);
    }
}

void STGV::handleFreeOverloaded(std::vector<std::string> & duplicates) {
    for (auto& e : duplicates) {
        std::string errorString = "Overloaded free function " + e;
        auto pair = std::make_pair(errorString, 0);
        symbolTable->addError(pair);
    }
}