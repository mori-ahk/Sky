//
// Created by Morteza Ahmadi on 2020-02-19.
//

#ifndef SKY_ASTNODE_H
#define SKY_ASTNODE_H

#include <string>
#include <vector>

class ASTNode {
public:
    ASTNode(std::string);
    ASTNode();
    ~ASTNode();
    std::string& getName();
    std::vector<ASTNode*>& getChildren();
private:
    std::string name;
    std::vector<ASTNode*> children;

};


#endif //SKY_ASTNODE_H
