//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_FUNCDECL_H
#define SKY_FUNCDECL_H


#include "../ASTNode.h"

class FuncDecl: public ASTNode {
public:
    FuncDecl(std::string name): ASTNode(name) {}
};


#endif //SKY_FUNCDECL_H
