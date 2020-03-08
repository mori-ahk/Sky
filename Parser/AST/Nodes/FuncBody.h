//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_FUNCBODY_H
#define SKY_FUNCBODY_H


#include "../ASTNode.h"

class FuncBody : public ASTNode {
public:
    FuncBody(std::string name) : ASTNode(name) {}
};


#endif //SKY_FUNCBODY_H
