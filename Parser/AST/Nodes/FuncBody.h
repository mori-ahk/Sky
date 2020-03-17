//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_FUNCBODY_H
#define SKY_FUNCBODY_H


#include "../ASTNode.h"

class FuncBody : public AST::ASTNode {
public:
    FuncBody(std::string name, Token* token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_FUNCBODY_H
