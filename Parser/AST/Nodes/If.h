//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_IF_H
#define SKY_IF_H

#include "../ASTNode.h"

class If : public AST::ASTNode {
public:
    If(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_IF_H
