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
    const std::string& getName();
    std::deque<ASTNode*>& getChildren();

    int getUniqueID();

    void addChildToLeft(ASTNode*);
    void addChildToRight(ASTNode*);
    void adoptChildren(std::deque<ASTNode*>);

private:
    std::string name;
    std::deque<ASTNode*> children;
    int uniqueID;
};


#endif //SKY_ASTNODE_H
