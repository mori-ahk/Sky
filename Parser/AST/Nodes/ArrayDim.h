//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_ARRAYDIM_H
#define SKY_ARRAYDIM_H


#include "../ASTNode.h"

class ArrayDim : public ASTNode {
public:
    ArrayDim(std::string name) : ASTNode(name) {}
};


#endif //SKY_ARRAYDIM_H
