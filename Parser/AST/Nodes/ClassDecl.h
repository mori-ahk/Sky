//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_CLASSDECL_H
#define SKY_CLASSDECL_H


#include "../ASTNode.h"

class ClassDecl: public ASTNode {
public:
    ClassDecl(std::string name) : ASTNode(name) {}

};


#endif //SKY_CLASSDECL_H
