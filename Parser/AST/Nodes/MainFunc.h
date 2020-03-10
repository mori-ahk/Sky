//
// Created by Morteza Ahmadi on 2020-03-10.
//

#ifndef SKY_MAINFUNC_H
#define SKY_MAINFUNC_H


#include "../ASTNode.h"

class MainFunc : public ASTNode {
public:
    MainFunc(std::string name): ASTNode(name) {}
    void accept(Visitor& visitor) override;
};


#endif //SKY_MAINFUNC_H
