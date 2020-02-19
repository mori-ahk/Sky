//
// Created by Morteza Ahmadi on 2020-02-19.
//

#ifndef SKY_ASTBUILDER_H
#define SKY_ASTBUILDER_H

#include <stack>
#include "ASTNode.h"
#include "SemanticActions.h"
class ASTBuilder {
public:

    ASTBuilder();
    ~ASTBuilder();

    void handle(std::string&);
    void push(ASTNode*);
    bool isIgnoreModeOn;

private:

    void createNode(std::string&);
    void insertLeftChild();
    void insertRightChild();
    void adoptChild();

    std::stack<ASTNode*> stack;

};


#endif //SKY_ASTBUILDER_H
