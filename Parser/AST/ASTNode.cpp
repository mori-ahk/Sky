//
// Created by Morteza Ahmadi on 2020-02-19.
//

#include "ASTNode.h"
#include "../../Visitors/Visitor.h"
static int counter = 0;


AST::ASTNode::ASTNode() {
    this->name = "";
    this->parent = nullptr;
}

AST::ASTNode::ASTNode(std::string name, int lineNumber) {
    this->name = name;
    this->lineNumber = lineNumber;
    uniqueID = counter++;
}

AST::ASTNode::~ASTNode() {}

std::string& AST::ASTNode::getName() {
    return name;
}

std::deque<AST::ASTNode*>& AST::ASTNode::getChildren() {
    return children;
}

AST::ASTNode* AST::ASTNode::getParent() {
    return parent;
}

AST::ASTNode* AST::ASTNode::getChild(int index) {
    return getChildren().at(index);
}

int& AST::ASTNode::getUniqueID() {
    return uniqueID;
}

int& AST::ASTNode::getLineNumber() {
    return lineNumber;
}

void AST::ASTNode::setParent(ASTNode * parent) {
    this->parent = parent;
}

void AST::ASTNode::addChildToLeft(ASTNode* node) {
    children.push_front(node);
//    std::cout << "adding to left children of " << this->name << ": ";
//    for (auto child : children) {
//        std::cout << child->getName() << " ";
//    }
//
//    std::cout << std::endl;
}

void AST::ASTNode::addChildToRight(ASTNode* node) {
    children.push_back(node);
//    std::cout << "adding to right children of " << this->name << ": ";
//    for (auto child : children) {
//        std::cout << child->getName() << " ";
//    }
//
//    std::cout << std::endl;
}

void AST::ASTNode::addChildToLeft(std::vector<ASTNode *> & childrenToBeInserted) {
    for (auto child : childrenToBeInserted) {
        children.push_front(child);
    }
}

void AST::ASTNode::adoptChildren(std::deque<ASTNode*> _children) {

    for (auto it = _children.begin() ; it != _children.end(); it++) {
        children.push_back(*it);
    }
//    std::cout << "adopting to right children of " << this->name << ": ";
//
//    for (auto child : children) {
//        std::cout << child->getName() << " ";
//    }
//
//    std::cout << std::endl;
}

void AST::ASTNode::accept(Visitor &visitor) {
    visitor.visit(this);
}