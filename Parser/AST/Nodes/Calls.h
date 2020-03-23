//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_CALLS_H
#define SKY_CALLS_H


#include "../ASTNode.h"

class Calls : public AST::ASTNode {
public:
    Calls(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_CALLS_H
