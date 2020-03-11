//
// Created by Morteza Ahmadi on 2020-02-19.
//

#include "ASTBuilder.h"
#include <iostream>



AST::ASTBuilder::ASTBuilder() {
    std::string program = "START";
    this->root = new ASTNode(program, 0);
    this->visualizer = new Visualizer();
    stack.push(root);

}

AST::ASTBuilder::~ASTBuilder() {}

AST::ASTNode* AST::ASTBuilder::getRoot() {
    return root;
}

void AST::ASTBuilder::createNode(std::string& rule) {
    stack.push(createCustomNode(rule));
}

void AST::ASTBuilder::push(std::string& nodeName, int lineNumber) {
    stack.push(createCustomNode(nodeName, lineNumber));
}

void AST::ASTBuilder::insertRightChild() {
    auto B = stack.top(); stack.pop();
    auto A = stack.top(); stack.pop();
    A->addChildToRight(B);
    stack.push(A);
}

void AST::ASTBuilder::insertLeftChild() {
    auto B = stack.top(); stack.pop();
    auto A = stack.top(); stack.pop();
    B->addChildToLeft(A);
    stack.push(B);

}

void AST::ASTBuilder::adoptChild() {
    auto B = stack.top(); stack.pop();
    auto A = stack.top(); stack.pop();
    A->adoptChildren(B->getChildren());
    stack.push(A);
}

void AST::ASTBuilder::constructListAndInsertAsChild() {
    auto B = stack.top(); stack.pop();
    std::vector<ASTNode*> childrenToBeInserted;
    childrenToBeInserted.push_back(B);
    while(stack.top()->getName() == B->getName()) {
        childrenToBeInserted.push_back(stack.top());
        stack.pop();
    }

    auto A = new ASTNode("call_list", 0);
    A->addChildToLeft(childrenToBeInserted);
    stack.push(A);
}

void AST::ASTBuilder::removeSelfIfOnlyHasOneChild() {
    auto B = stack.top(); stack.pop();
    if (B->getChildren().size() == 1) B = B->getChildren().at(0);
    stack.push(B);
}

void AST::ASTBuilder::handle(std::string& action, std::string& LHS) {
    if (isIgnoreModeOn) return;
//    printStack();
//    std::cout << "LHS: " << LHS << " action: " << action << std::endl;
    std::string action_number = action.substr(0, 2);
    if (action_number == "@1") {
        //Extract #optiona_custom_name for the AST node.
        if (action.size() > 2) {
            std::string arg = action.substr(4);
            createNode(arg);
        } else createNode(LHS);
    }

    else if (action_number == "@2") insertRightChild();
    else if (action_number == "@3") adoptChild();
    else if (action_number == "@4") insertLeftChild();
    else if (action_number == "@5") constructListAndInsertAsChild();
    else if (action_number == "@6") stack.pop();
    else removeSelfIfOnlyHasOneChild();
}

void AST::ASTBuilder::printStack() {
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


void AST::ASTBuilder::visualize() {
    visualizer->visualize(root);
}


AST::ASTNode* AST::ASTBuilder::createCustomNode(std::string& nodeName, int lineNumber) {
    if (nodeName == "CLASSDECLARATIONS") return new ClassDecls(nodeName, lineNumber);
    else if (nodeName == "class") return new ClassDecl(nodeName, lineNumber);
    else if (nodeName == "func_decl") return new FuncDecl(nodeName, lineNumber);
    else if (nodeName == "params") return new FuncParams(nodeName, lineNumber);
    else if (nodeName == "func_def") return new FuncDef(nodeName,lineNumber);
    else if (nodeName == "ARRAYDIMENSIONS") return new ArrayDim(nodeName, lineNumber);
    else if (nodeName == "LOCALSCOPE") return new Local(nodeName, lineNumber);
    else if (nodeName == "PROGRAM") return new Program(nodeName, lineNumber);
    else if (nodeName == "variable") return new VarDecl(nodeName, lineNumber);
    else if (nodeName == "func_body") return new FuncBody(nodeName, lineNumber);
    else if (nodeName == "main") return new MainFunc(nodeName, lineNumber);
    else return new ASTNode(nodeName, lineNumber);
}