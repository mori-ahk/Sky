//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_FUNCDECL_H
#define SKY_FUNCDECL_H


#include "../ASTNode.h"

class FuncDecl : public AST::ASTNode {
public:
    FuncDecl(std::string name, Token* token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_FUNCDECL_H
