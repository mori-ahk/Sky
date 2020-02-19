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

std::vector<ASTNode*>& ASTNode::getChildren() {
    return children;
}