//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_COMPAREOP_H
#define SKY_COMPAREOP_H

#include "../ASTNode.h"

class CompareOp : public AST::ASTNode {
public:
    CompareOp(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_COMPAREOP_H
