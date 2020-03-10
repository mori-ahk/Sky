//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_LOCAL_H
#define SKY_LOCAL_H


#include "../ASTNode.h"

class Local : public ASTNode {
public:
    Local(std::string name, int lineNumber) : ASTNode(name, lineNumber) {}
    void accept(Visitor& visitor) override;
};


#endif //SKY_LOCAL_H
