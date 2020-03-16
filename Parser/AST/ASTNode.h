//
// Created by Morteza Ahmadi on 2020-02-19.
//

#ifndef SKY_ASTNODE_H
#define SKY_ASTNODE_H


#include <string>
#include <vector>
#include <deque>

class Visitor;
namespace AST {
    class ASTNode {
    public:
        ASTNode(std::string, int);
        ASTNode();
        ~ASTNode() = default;

        std::string &getName();
        std::deque<ASTNode *> &getChildren();

        ASTNode* getChild(int);
        ASTNode* getParent();

        int& getLineNumber();
        int& getUniqueID();

        void setParent(ASTNode *);
        void addChildToLeft(ASTNode *);
        void addChildToRight(ASTNode *);
        void addChildToLeft(const std::vector<ASTNode*>&);
        void adoptChildren(const std::deque<ASTNode*>&);

        virtual void accept(Visitor &visitor);

    private:

        std::string name;
        std::deque<ASTNode *> children;
        ASTNode *parent;
        int uniqueID;
        int lineNumber;
    };
}

#endif //SKY_ASTNODE_H
