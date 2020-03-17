//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_ARRAYDIM_H
#define SKY_ARRAYDIM_H


#include "../ASTNode.h"

class ArrayDim : public AST::ASTNode {
public:
    ArrayDim(std::string name, int lineNumber) : ASTNode(name, lineNumber) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_ARRAYDIM_H
