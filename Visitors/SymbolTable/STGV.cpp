//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "STGV.h"
#include <iostream>
#include <vector>


STGV::STGV(AST::ASTNode *root) {
    this->symbolTable = new Semantic::SymbolTable();
    this->detector = new Semantic::Detector(this->symbolTable);
    root->getChild(0)->accept(*this);
}

void STGV::visit(Program *node) {
    for (auto child : node->getChildren()) {
        child->accept(*this);
    }

    //detect for errors
    detector->detect();
}

void STGV::visit(FuncDef *node) {
    std::string namespaceName;

    AST::ASTNode *signature = node->getChild(0);
    AST::ASTNode *funcBody = node->getChild(1);
    auto isClassFunc = [&signature]() {
        return signature->getChildren().size() == 4;
    };

    //if the function belongs to a class and has a namespace;
    if (isClassFunc()) namespaceName = signature->getChild(0)->getName();

    std::string funcName;
    if (isClassFunc()) funcName = signature->getChild(1)->getName();
    else funcName = signature->getChild(0)->getName();

    std::string returnType = isClassFunc() ? signature->getChild(3)->getName() : signature->getChild(2)->getName();
    Function *function = createTempFunction(node, funcName, returnType);

    //check if the class function signature and defined function signature match.
    if (isClassFunc()) {
        try {
            auto classFunction = symbolTable->getClass(namespaceName)->getFunction(funcName, function);
            classFunction->isDefined = true;
        } catch (Semantic::Err::UndeclaredClass &undeclaredClass) {
            detector->addError(std::string(undeclaredClass.what()));
            return;
        } catch (Semantic::Err::UndeclaredFunction &undeclaredFunc) {
            detector->addError(std::string(undeclaredFunc.what()));
            return;
        }
    }

    //iterating on local vars
    AST::ASTNode *localVars = funcBody->getChild(0);
    for (auto &localVar : localVars->getChildren()) {
        Variable *variable = createVar(localVar);

        //throw a semantic error if `variable` is a duplicate variable in the `function`'s local scope.
        try {
            function->addVariable(variable);
        } catch (Semantic::Err::DuplicateDataMember &duplicateLocalVar) {
            int position = localVar->getChild(1)->getLineNumber();
            detector->addError(std::string(duplicateLocalVar.what()));
        }

        //fetching the class that this function corresponds to and add local variable to its scope
        if (isClassFunc()) {
            auto classFunction = symbolTable->classes.at(namespaceName)->getFunction(funcName, function);
            classFunction->addVariable(variable);
        }
    }

    if (!isClassFunc()) symbolTable->addFunction(funcName, function);
}

void STGV::visit(VarDecl *node) {
    Variable *variable = createVar(node);
    try {
        symbolTable->classes.at(node->getParent()->getName())->addVariable(variable->getName(), variable);
    } catch (Semantic::Err::DuplicateDataMember &duplicateDataMember) {
        detector->addError(std::string(duplicateDataMember.what()));
        return;
    }
}

void STGV::visit(FuncDecl *node) {
    std::string visibilityString = node->getChild(0)->getName();
    Visibility visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
    std::string funcName = node->getChild(1)->getName();
    std::string returnType = node->getChild(3)->getName();
    Function *function = new Function(visibility, funcName, returnType, {}, {}, node->getChild(1)->getLineNumber());

    symbolTable->getClass(node->getParent()->getName())->addFunction(funcName, function);

    //setting the parent of `funcName` node to `className` node
    node->getChild(1)->setParent(node->getParent());
    //setting the parent of `params` node to `funcName` node
    node->getChild(2)->setParent(node->getChild(1));

    node->getChild(2)->accept(*this);
}

void STGV::visit(ClassDecl *node) {
    //Creating a class entry
    std::string className = node->getChild(0)->getName();
    std::vector<std::string> inherits;
    //constructing a string indicating all the parent class
    for (auto &child : node->getChild(1)->getChildren()) {
        inherits.push_back(child->getName());
    }

    Class *classEntry = new Class(className, className, inherits, node->getChild(0)->getLineNumber());
    try {
        symbolTable->addClass(className, classEntry);
    } catch (Semantic::Err::DuplicateClassDecl &duplicateClassDecl) {
        detector->addError(std::string(duplicateClassDecl.what()));
    }

    for (auto &child : node->getChild(2)->getChildren()) {
        //setting the parent of each member in `MEMBERDECLARATIONS` to `className` node
        child->setParent(node->getChild(0));
        child->accept(*this);
    }
}

void STGV::visit(ClassDecls *node) {
    for (auto &child : node->getChildren()) {
        child->accept(*this);
    }
}

void STGV::visit(FuncParams *node) {
    for (auto &child: node->getChildren()) {
        //setting the parent of each `param` node to `funcName` node
        child->setParent(node->getParent());

        Variable *variable = createVar(child);
        std::string className = node->getParent()->getParent()->getName();
        std::string funcName = node->getParent()->getName();
        try {
            symbolTable->classes.at(className)->getFunctions().at(funcName).back()->addParam(variable);
        } catch (Semantic::Err::DuplicateFuncParam &duplicateFuncParam) {
            detector->addError(std::string(duplicateFuncParam.what()));
        }
    }
}

void STGV::visit(MainFunc *node) {
    AST::ASTNode *funcBody = node->getChild(0);
    AST::ASTNode *localVars = funcBody->getChild(0);
    symbolTable->main->setPosition(node->getLineNumber());

    for (auto &var : localVars->getChildren()) {
        Variable *variable = createVar(var);
        try {
            symbolTable->main->addVariable(variable);
        } catch (Semantic::Err::DuplicateDataMember &duplicateLocalVar) {
            detector->addError(std::string(duplicateLocalVar.what()));
        }
    }
}

void STGV::visit(AST::ASTNode *node) {
    for (auto &child : node->getChildren()) {
        child->setParent(node->getParent());
        child->accept(*this);
    }
}

Variable *STGV::createVar(AST::ASTNode *node) {
    int startIndex = node->getChildren().size() == 4 ? 1 : 0;
    Visibility visibility = Visibility::PRIVATE;

    if (node->getChildren().size() == 4) {
        std::string visibilityString = node->getChildren().at(0)->getName();
        visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
    }

    std::string type = node->getChild(startIndex)->getName();
    if (node->getChild(startIndex++)->getType() == "id") {
        try {
            symbolTable->getClass(type);
        } catch (Semantic::Err::UndeclaredClass& undeclaredClass) {
            detector->addError(std::string(undeclaredClass.what()));
        }
    }

    std::string varName = node->getChild(startIndex)->getName();
    std::vector<int> dimensions;

    AST::ASTNode *dimNodeToIterate = node->getChildren().size() == 4 ? node->getChild(3) : node->getChild(2);
    for (auto &arrayDimensionChild: dimNodeToIterate->getChildren()) {
        try {
            int dimension = std::stoi(arrayDimensionChild->getChild(0)->getName());
            dimensions.push_back(dimension);
        } catch (const std::invalid_argument &invalid_argument) {}
    }
    return new Variable(visibility, varName, type, dimensions, node->getChild(startIndex)->getLineNumber());
}

Function *STGV::createTempFunction(AST::ASTNode *node, std::string &funcName, std::string &returnType) {
    AST::ASTNode *signature = node->getChild(0);
    auto isClassFunc = [&signature]() {
        return signature->getChildren().size() == 4;
    };

    Function *function = new Function(Visibility::PUBLIC, funcName, returnType, {}, {}, signature->getChild(0)->getLineNumber());

    //iterating on params
    AST::ASTNode *params = isClassFunc() ? signature->getChild(2) : signature->getChild(1);

    for (auto &param: params->getChildren()) {
        Variable *variable = createVar(param);

        //throw a semantic error if `variable` is a duplicate param in the `function`
        try {
            function->addParam(variable);
        } catch (Semantic::Err::DuplicateFuncParam &duplicateParam) {
            detector->addError(std::string(duplicateParam.what()));
        }
    }

    return function;
}

//Symbol table visitors do not need to implement these functions
//but they have to have an implementation to make the compiler happy

void STGV::visit(ArrayDim *node) {}

void STGV::visit(FuncBody *node) {}

void STGV::visit(Local *node) {}

void STGV::visit(AddOp *node) {}

void STGV::visit(AssignOp *node) {}

void STGV::visit(Calls *node) {}

void STGV::visit(Call *node) {}

void STGV::visit(CompareOp *node) {}

void STGV::visit(FuncCall *node) {}

void STGV::visit(If *node) {}

void STGV::visit(MultOp *node) {}

void STGV::visit(Read *node) {}

void STGV::visit(Return *node) {}

void STGV::visit(Sign *node) {}

void STGV::visit(Statements *node) {}

void STGV::visit(While *node) {}

void STGV::visit(Write *node) {}


