//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_VARDECL_H
#define SKY_VARDECL_H


#include "../ASTNode.h"

class VarDecl : public AST::ASTNode {
public:
    VarDecl(std::string name, Token* token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_VARDECL_H
