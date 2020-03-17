//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_PROGRAM_H
#define SKY_PROGRAM_H


#include "../ASTNode.h"

class Program : public AST::ASTNode {
public:
    Program(std::string name, int lineNumber) : ASTNode(name, lineNumber) {}

    void accept(Visitor &visitor) override;
};


#endif //SKY_PROGRAM_H
