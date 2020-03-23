//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_STATEMENTS_H
#define SKY_STATEMENTS_H

#include "../ASTNode.h"

class Statements : public AST::ASTNode {
public:
    Statements(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};

#endif //SKY_STATEMENTS_H
