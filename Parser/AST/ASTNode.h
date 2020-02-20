//
// Created by Morteza Ahmadi on 2020-02-19.
//

#ifndef SKY_ASTNODE_H
#define SKY_ASTNODE_H

#include <string>
#include <vector>
#include <deque>

class ASTNode {
public:
    ASTNode(std::string&);
    ASTNode();
    ~ASTNode();
    std::string& getName();
    std::deque<ASTNode*>& getChildren();

    void addChildToLeft(ASTNode*);
    void addChildToRight(ASTNode*);
    void adoptChildren(std::deque<ASTNode*>);

private:
    std::string name;
    std::deque<ASTNode*> children;

};


#endif //SKY_ASTNODE_H
