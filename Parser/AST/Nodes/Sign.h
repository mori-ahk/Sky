//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_SIGN_H
#define SKY_SIGN_H

#include "../ASTNode.h"

class Sign : public AST::ASTNode {
public:
    Sign(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_SIGN_H
