//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_WRITE_H
#define SKY_WRITE_H

#include "../ASTNode.h"

class Write : public AST::ASTNode {
public:
    Write(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_WRITE_H
