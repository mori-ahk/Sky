//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_MULTOP_H
#define SKY_MULTOP_H


#include "../ASTNode.h"

class MultOp : public AST::ASTNode {
public:
    MultOp(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_MULTOP_H
