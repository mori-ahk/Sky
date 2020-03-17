//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_CALL_H
#define SKY_CALL_H


#include "../ASTNode.h"

class Call : public AST::ASTNode {
public:
    Call(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_CALL_H
