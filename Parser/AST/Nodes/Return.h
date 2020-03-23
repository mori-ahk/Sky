//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_RETURN_H
#define SKY_RETURN_H

#include "../ASTNode.h"

class Return : public AST::ASTNode {
public:
    Return(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_RETURN_H
