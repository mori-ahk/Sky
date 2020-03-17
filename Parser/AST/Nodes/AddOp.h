//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_ADDOP_H
#define SKY_ADDOP_H

#include "../ASTNode.h"

class AddOp : public AST::ASTNode {
public:
    AddOp(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_ADDOP_H
