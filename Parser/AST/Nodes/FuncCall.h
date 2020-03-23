//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_FUNCCALL_H
#define SKY_FUNCCALL_H


#include "../ASTNode.h"

class FuncCall : public AST::ASTNode {
public:
    FuncCall(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_FUNCCALL_H
