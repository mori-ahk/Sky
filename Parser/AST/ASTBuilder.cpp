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

ASTNode* ASTBuilder::getRoot() {
    return root;
}

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
    printStack();
    std::cout << "LHS: " << LHS << " action: " << action << std::endl;
    std::string action_number = action.substr(0, 2);
    if (action_number == "@1") {
        if (action.size() > 2) {
            std::string arg = action.substr(4);
            createNode(arg);
        } else createNode(LHS);
    }

    else if (action_number == "@2") insertRightChild();
    else if (action_number == "@3") adoptChild();
    else insertLeftChild();
}

void ASTBuilder::printStack() {
    std::vector<ASTNode*> v;
    testStack = stack;
    while(!testStack.empty()) {
        v.push_back(testStack.top());
        testStack.pop();
    }

    for (int i = v.size() - 1; i > -1 ; i--) {
        std::cout << v.at(i)->getName() << "| ";
    }

    std::cout << std::endl;
}
