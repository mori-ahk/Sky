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
    ASTNode(std::string);
    ASTNode();
    ~ASTNode();
    const std::string& getName();
    std::deque<ASTNode*>& getChildren();
    ASTNode* getParent();
    int getUniqueID();

    void addChildToLeft(ASTNode*);
    void addChildToRight(ASTNode*);
    void addChildToLeft(std::vector<ASTNode*>&);
    void adoptChildren(std::deque<ASTNode*>);

private:

    std::string name;
    std::deque<ASTNode*> children;
    ASTNode* parent;
    int uniqueID;

};


#endif //SKY_ASTNODE_H
