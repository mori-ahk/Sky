//
// Created by Morteza Ahmadi on 2020-02-19.
//

#include "ASTBuilder.h"


ASTBuilder::ASTBuilder() {
    ASTNode* root = new ASTNode("PROGRAM");
    stack.push(root);
}

ASTBuilder::~ASTBuilder() {}

void ASTBuilder::createNode(std::string& rule) {
    ASTNode* node = new ASTNode(rule);
    stack.push(node);
}

void ASTBuilder::insertRightChild() {
    auto B = stack.top(); stack.pop();
    auto A = stack.top(); stack.pop();
    A->addChildToRight(B);
    stack.push(A);
}

void ASTBuilder::insertLeftChild() {
    auto B = stack.top(); stack.pop();
    auto A = stack.top(); stack.pop();
    B->addChildToLeft(A);
    stack.push(B);
}

void ASTBuilder::adoptChild() {
    auto B = stack.top(); stack.pop();
    auto A = stack.top(); stack.pop();
    A->adoptChildren(B->getChildren());
    stack.push(A);
}


void ASTBuilder::handle(std::string& action) {
    std::string action_number = action.substr(0, 2);
    if (action_number == "@1") createNode(action);
    else if (action_number == "@2") insertRightChild();
    else if (action_number == "@3") adoptChild();
    else insertLeftChild();
}

