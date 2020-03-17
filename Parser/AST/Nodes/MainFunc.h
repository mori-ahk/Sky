//
// Created by Morteza Ahmadi on 2020-03-10.
//

#ifndef SKY_MAINFUNC_H
#define SKY_MAINFUNC_H


#include "../ASTNode.h"

class MainFunc : public AST::ASTNode {
public:
    MainFunc(std::string name, Token* token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_MAINFUNC_H
