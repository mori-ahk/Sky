//
// Created by Morteza Ahmadi on 2020-03-17.
//

#ifndef SKY_READ_H
#define SKY_READ_H

#include "../ASTNode.h"

class Read : public AST::ASTNode {
public:
    Read(std::string name, Token *token) : ASTNode(std::move(name), token) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_READ_H
