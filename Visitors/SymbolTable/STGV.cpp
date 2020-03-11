//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "STGV.h"
#include <iostream>

STGV::STGV(ASTNode* root) {
    this->symbolTable = new Semantic::SymbolTable();
    root->getChildren().at(0)->accept(*this);
}
void STGV::visit(Program *node) {
    for(auto child : node->getChildren()) {
        child->accept(*this);
    }
}

void STGV::visit(Local *node) {

}

void STGV::visit(FuncDef *node) {

    std::string namespaceName;

    auto signature = node->getChildren().at(0);
    auto funcBody = node->getChildren().at(1);
    //if the function belongs to a class and has a namespace;
    if (signature->getChildren().size() == 4) namespaceName = signature->getChildren().at(0)->getName();

    std::string funcName;
    if (signature->getChildren().size() == 4) funcName = signature->getChildren().at(1)->getName();
    else funcName = signature->getChildren().at(0)->getName();
    std::string returnType = signature->getChildren().at(2)->getName();
    Function* function = new Function(Visibility::PUBLIC, funcName, returnType, {}, {});

    //iterating on params
    auto params = signature->getChildren().at(1);
    for (auto param: params->getChildren()) {
        Variable *variable = createVar(param);
        function->addParam(variable);
    }

    //iterating on local vars
    auto localVars = funcBody->getChildren().at(0);
    for (auto localVar : localVars->getChildren()) {
        Variable* variable = createVar(localVar);
        function->addVariable(variable);
        //fetching the class that this function corresponds to and add local variable to its scope
        if (!namespaceName.empty()) symbolTable->classes.at(namespaceName)->getFunctions().at(funcName)->addVariable(variable);
    }

    if (signature->getChildren().size() == 3) symbolTable->freeFunctions[funcName] = function;
}

void STGV::visit(VarDecl *node) {
    Variable* variable = createVar(node);
    symbolTable->classes.at(node->getParent()->getName())->addVariable(variable->getName(), variable);
}

void STGV::visit(ArrayDim *node) {}

void STGV::visit(FuncBody *node) {}

void STGV::visit(FuncDecl *node) {
    std::string visibilityString = node->getChildren().at(0)->getName();
    Visibility  visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
    std::string funcName =  node->getChildren().at(1)->getName();
    std::string returnType = node->getChildren().at(3)->getName();
    Function* function = new Function(visibility, funcName, returnType, {}, {});
    symbolTable->classes.at(node->getParent()->getName())->addFunction(funcName, function);

    //setting the parent of `funcName` node to `className` node
    node->getChildren().at(1)->setParent(node->getParent());
    //setting the parent of `params` node to `funcName` node
    node->getChildren().at(2)->setParent(node->getChildren().at(1));

    node->getChildren().at(2)->accept(*this);
}

void STGV::visit(ClassDecl *node) {
    //Creating a class entry
    std::string className = node->getChildren().at(0)->getName();
    std::string inherits = "";
    //constructing a string indicating all the parent class
    for(auto child : node->getChildren().at(1)->getChildren()) {
        inherits += child->getName() + " ";
    }

    Class* classEntry = new Class(className, className, inherits);
    symbolTable->addClass(className, classEntry);

    for(auto child : node->getChildren().at(2)->getChildren()) {

       //setting the parent of each member in `MEMBERDECLARATIONS` to `className` node
       child->setParent(node->getChildren().at(0));
       child->accept(*this);
    }
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
        symbolTable->classes.at(node->getParent()->getParent()->getName())->getFunctions().at(node->getParent()->getName())->addParam(variable);
    }
}

void STGV::visit(MainFunc* node) {
    auto funcBody = node->getChildren().at(0);
    auto localVars = funcBody->getChildren().at(0);

    for(auto var : localVars->getChildren()) {
        Variable* variable = createVar(var);
        symbolTable->main->addVariable(variable);
    }
}

void STGV::visit(ASTNode *node) {
    for(auto child : node->getChildren()) {
        child->setParent(node->getParent());
        child->accept(*this);

    }
}


Variable* STGV::createVar(ASTNode* node) {
    int startIndex = node->getChildren().size() == 4 ? 1 : 0;
    Visibility  visibility = Visibility::PRIVATE;
    if (node->getChildren().size() == 4) {
        std::string visibilityString = node->getChildren().at(0)->getName();
        Visibility visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
    }
    std::string varName = node->getChildren().at(startIndex++)->getName();
    std::string type = node->getChildren().at(startIndex++)->getName();
    std::vector<int> dimensions;

    auto dimNodeToIterate = node->getChildren().size() == 4 ? node->getChildren().at(3) : node->getChildren().at(2);
    for (auto arrayDimensionChild: dimNodeToIterate->getChildren()) {
        try {
            int dimension = std::stoi(arrayDimensionChild->getChildren().at(0)->getName());
            dimensions.push_back(dimension);
        } catch (const std::invalid_argument& invalid_argument) {}
    }

    return new Variable(visibility, type, varName, dimensions);
}
