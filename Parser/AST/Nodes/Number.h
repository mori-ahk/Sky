//
// Created by Morteza Ahmadi on 2020-04-09.
//

#ifndef SKY_NUMBER_H
#define SKY_NUMBER_H

#include "../ASTNode.h"

class Number : public AST::ASTNode {
public:
    Number(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_NUMBER_H
