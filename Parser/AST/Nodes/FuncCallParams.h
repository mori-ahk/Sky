//
// Created by Morteza Ahmadi on 2020-04-12.
//

#ifndef SKY_FUNCCALLPARAMS_H
#define SKY_FUNCCALLPARAMS_H

#include "../ASTNode.h"

class FuncCallParams : public AST::ASTNode {
public:
    FuncCallParams(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_FUNCCALLPARAMS_H
