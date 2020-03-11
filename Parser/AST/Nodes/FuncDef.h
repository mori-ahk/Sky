//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_FUNCDEF_H
#define SKY_FUNCDEF_H


#include "../ASTNode.h"

class FuncDef : public AST::ASTNode {
public:
    FuncDef(std::string name, int lineNumber) : ASTNode(name, lineNumber) {}
    void accept(Visitor& visitor) override;
};


#endif //SKY_FUNCDEF_H
