//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_CLASSDECL_H
#define SKY_CLASSDECL_H

#include "../ASTNode.h"

class ClassDecl : public AST::ASTNode {
public:
    ClassDecl(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_CLASSDECL_H
