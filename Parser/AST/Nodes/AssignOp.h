//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_ASSIGNOP_H
#define SKY_ASSIGNOP_H

#include "../ASTNode.h"

class AssignOp : public AST::ASTNode {
public:
    AssignOp(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;

};


#endif //SKY_ASSIGNOP_H
