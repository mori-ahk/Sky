//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_WHILE_H
#define SKY_WHILE_H

#include "../ASTNode.h"

class While : public AST::ASTNode {
public:
    While(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_WHILE_H
