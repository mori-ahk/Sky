//
// Created by Morteza Ahmadi on 2020-03-08.
//

#include "STGV.h"
#include <iostream>
#include "../../SymbolTable/Entries/Class.h"
STGV::STGV(ASTNode* root) {
    this->symbolTable = new SymbolTable();
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

}

void STGV::visit(VarDecl *node) {
    std::string visibilityString = node->getChildren().at(0)->getName();
    Visibility  visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
    std::string type = node->getChildren().at(1)->getName();
    std::string varName = node->getChildren().at(2)->getName();
    std::vector<int> dimensions;
    for (auto child: node->getChildren().at(3)->getChildren()) {
        dimensions.push_back(std::stoi(child->getChildren().at(0)->getName()));
    }

    Variable* variable = new Variable(visibility, type, varName, dimensions);
    symbolTable->classes.at(node->getParent()->getName())->addVariable(varName, variable);

}

void STGV::visit(ArrayDim *node) {

}

void STGV::visit(FuncBody *node) {

}

void STGV::visit(FuncDecl *node) {
    std::string visibilityString = node->getChildren().at(0)->getName();
    Visibility  visibility = visibilityString == "private" ? Visibility::PRIVATE : Visibility::PUBLIC;
    std::string returnType = node->getChildren().at(3)->getName();

    for(auto child : node->getChildren().at(2)->getChildren()) {
        child->accept(*this);
    }


}

void STGV::visit(ClassDecl *node) {
    //Creating a class entry
    std::string className = node->getChildren().at(0)->getName();
    std::string inherits = "";
    for(auto child : node->getChildren().at(1)->getChildren()) {
        inherits += child->getName() + " ";
    }

    Class* classEntry = new Class(className, className, inherits);
    symbolTable->classes[className] = classEntry;

    for(auto child : node->getChildren()) {

       child->setParent(node);
       child->accept(*this);
    }
}

void STGV::visit(ClassDecls *node) {
    for(auto child : node->getChildren()) {
        child->accept(*this);
    }
}

void STGV::visit(FuncParams *node) {

}

void STGV::visit(ASTNode *node) {
    for(auto child : node->getChildren()) {
        child->setParent(node->getParent());
        child->accept(*this);

    }
}
