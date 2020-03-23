//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_FUNCPARAMS_H
#define SKY_FUNCPARAMS_H


#include "../ASTNode.h"

class FuncParams : public AST::ASTNode {
public:
    FuncParams(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_FUNCPARAMS_H
