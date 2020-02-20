//
// Created by Morteza Ahmadi on 2020-02-19.
//

#include "ASTBuilder.h"
#include <iostream>

ASTBuilder::ASTBuilder() {
    std::string program = "START";
    root = new ASTNode(program);
    stack.push(root);
}

ASTBuilder::~ASTBuilder() {}

void ASTBuilder::createNode(std::string& rule) {
    ASTNode* node = new ASTNode(rule);
    stack.push(node);
}

void ASTBuilder::push(ASTNode* node) {
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


void ASTBuilder::handle(std::string& action, std::string& LHS) {
    std::string action_number = action.substr(0, 2);
    if (action_number == "@1") createNode(LHS);
    else if (action_number == "@2") insertRightChild();
    else if (action_number == "@3") adoptChild();
    else insertLeftChild();
    printStack();
}

void ASTBuilder::printStack() {
    auto B = stack.top(); stack.pop();
    std::cout << "B: " << B->getName() << std::endl;
    auto A = stack.top(); stack.pop();
    std::cout << "A: " << A->getName() << std::endl;
    stack.push(A);
    stack.push(B);
}
