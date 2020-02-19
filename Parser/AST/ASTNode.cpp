//
// Created by Morteza Ahmadi on 2020-02-19.
//

#include "ASTNode.h"

ASTNode::ASTNode() {
    this->name = std::string();
    this->children = {};
}

ASTNode::ASTNode(std::string name) {
    this->name = name;
    this->children = {};
}

ASTNode::~ASTNode() {
    for (auto& child : children) {
        delete child;
    }
}

std::string& ASTNode::getName() {
    return name;
}

std::deque<ASTNode*>& ASTNode::getChildren() {
    return children;
}

void ASTNode::addChildToLeft(ASTNode* node) {
    children.push_back(node);
}

void ASTNode::addChildToRight(ASTNode* node) {
    children.push_front(node);
}

void ASTNode::adoptChildren(std::deque<ASTNode*> _children) {
    for (auto it = _children.begin() ; it != _children.end(); it++) {
        children.push_front(*it);
    }
}