//
// Created by Morteza Ahmadi on 2020-02-19.
//

#include "ASTNode.h"
#include <iostream>

static int counter = 0;

ASTNode::ASTNode() {
    this->name = "";
}

ASTNode::ASTNode(std::string& name) {
    this->name = name;
    uniqueID = counter++;
}

ASTNode::~ASTNode() {}

const std::string& ASTNode::getName() {
    return name;
}

std::deque<ASTNode*>& ASTNode::getChildren() {
    return children;
}

void ASTNode::addChildToLeft(ASTNode* node) {
    children.push_front(node);
    std::cout << "adding to left children of " << this->name << ": ";
    for (auto child : children) {
        std::cout << child->getName() << " ";
    }

    std::cout << std::endl;
}

void ASTNode::addChildToRight(ASTNode* node) {
    children.push_back(node);
    std::cout << "adding to right children of " << this->name << ": ";
    for (auto child : children) {
        std::cout << child->getName() << " ";
    }

    std::cout << std::endl;
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
    std::cout << "adopting to right children of " << this->name << ": ";

    for (auto child : children) {
        std::cout << child->getName() << " ";
    }

    std::cout << std::endl;
}

int ASTNode::getUniqueID() {
    return uniqueID;
}