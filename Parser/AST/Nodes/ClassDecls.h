//
// Created by Morteza Ahmadi on 2020-03-08.
//

#ifndef SKY_CLASSDECLS_H
#define SKY_CLASSDECLS_H


#include "../ASTNode.h"

class ClassDecls : public ASTNode {
public:
    ClassDecls(std::string name, int lineNumber) : ASTNode(name, lineNumber) {}
    void accept(Visitor& visitor) override;
};


#endif //SKY_CLASSDECLS_H
