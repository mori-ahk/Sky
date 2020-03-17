//
// Created by Morteza Ahmadi on 2020-02-19.
//

#include "ASTNode.h"

#include <utility>
#include "../../Visitors/Visitor.h"

static int counter = 0;

AST::ASTNode::ASTNode() {
    this->name = "";
    this->parent = nullptr;
}

AST::ASTNode::ASTNode(std::string name, int lineNumber) {
    this->name = std::move(name);
    this->lineNumber = lineNumber;
    uniqueID = counter++;
}

std::string &AST::ASTNode::getName() {
    return name;
}

std::deque<AST::ASTNode *> &AST::ASTNode::getChildren() {
    return children;
}

AST::ASTNode *AST::ASTNode::getParent() {
    return parent;
}

AST::ASTNode *AST::ASTNode::getChild(int index) {
    return getChildren().at(index);
}

int &AST::ASTNode::getUniqueID() {
    return uniqueID;
}

int &AST::ASTNode::getLineNumber() {
    return lineNumber;
}

void AST::ASTNode::setParent(ASTNode *parent) {
    this->parent = parent;
}

void AST::ASTNode::addChildToLeft(ASTNode *node) {
    children.push_front(node);
}

void AST::ASTNode::addChildToRight(ASTNode *node) {
    children.push_back(node);
}

void AST::ASTNode::addChildToLeft(const std::vector<ASTNode *> &childrenToBeInserted) {
    for (auto &child : childrenToBeInserted) {
        children.push_front(child);
    }
}

void AST::ASTNode::adoptChildren(const std::deque<ASTNode *> &_children) {
    for (auto &child : _children) {
        children.push_back(child);
    }
}

void AST::ASTNode::accept(Visitor &visitor) {
    visitor.visit(this);
}