//
// Created by Morteza Ahmadi on 2020-02-19.
//

#include "ASTNode.h"
#include "../../Visitors/Visitor.h"
static int counter = 0;


ASTNode::ASTNode() {
    this->name = "";
    this->parent = nullptr;
}

ASTNode::ASTNode(std::string name, int lineNumber) {
    this->name = name;
    this->lineNumber = lineNumber;
    uniqueID = counter++;
}

ASTNode::~ASTNode() {}

std::string& ASTNode::getName() {
    return name;
}

std::deque<ASTNode*>& ASTNode::getChildren() {
    return children;
}

ASTNode* ASTNode::getParent() {
    return parent;
}

int& ASTNode::getUniqueID() {
    return uniqueID;
}

int& ASTNode::getLineNumber() {
    return lineNumber;
}

void ASTNode::setParent(ASTNode * parent) {
    this->parent = parent;
}

void ASTNode::addChildToLeft(ASTNode* node) {
    children.push_front(node);
//    std::cout << "adding to left children of " << this->name << ": ";
//    for (auto child : children) {
//        std::cout << child->getName() << " ";
//    }
//
//    std::cout << std::endl;
}

void ASTNode::addChildToRight(ASTNode* node) {
    children.push_back(node);
//    std::cout << "adding to right children of " << this->name << ": ";
//    for (auto child : children) {
//        std::cout << child->getName() << " ";
//    }
//
//    std::cout << std::endl;
}

void ASTNode::addChildToLeft(std::vector<ASTNode *> & childrenToBeInserted) {
    for (auto child : childrenToBeInserted) {
        children.push_front(child);
    }
}

void ASTNode::adoptChildren(std::deque<ASTNode*> _children) {

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

void ASTNode::accept(Visitor &visitor) {
    visitor.visit(this);
}