//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_PROGRAM_H
#define SKY_PROGRAM_H


#include "../ASTNode.h"

class Program : public ASTNode {
public:
    Program(std::string name) : ASTNode(name) {}
    void accept(Visitor& visitor) override;
};


#endif //SKY_PROGRAM_H
